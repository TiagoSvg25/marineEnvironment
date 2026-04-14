// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/AnimalAIController.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>



AAnimalAIController::AAnimalAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAnimalAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn); 
    InitialZ = getModel()->GetActorLocation().Z;

    getModel()->setState("Idle");

    CurrentDirection = FMath::VRand();
    FVector2D Random2D = FMath::RandPointInCircle(1.0f);

    FVector CurrentLocation = getModel()->GetActorLocation();

    FVector RandomOffset = FMath::VRand() * 200.0f;

    FVector NewTarget = CurrentLocation + RandomOffset;

    NewTarget.Z = FMath::Min(NewTarget.Z, getModel()->getMaxDepthRange());

    getModel()->setTargetLocation(NewTarget);

}
void AAnimalAIController::DrawDebugVisionCone()
{
    if (!getModel()) return;

    FVector Location = getModel()->GetActorLocation();
    FVector Forward = getModel()->GetActorForwardVector();
    float Radius = getModel()->getAwarenessRadius();
    float HalfAngle = getModel()->getAngleVision() * 0.5f;

    DrawDebugCone(
        GetWorld(),
        Location,
        Forward,
        Radius,
        FMath::DegreesToRadians(HalfAngle),
        FMath::DegreesToRadians(HalfAngle),
        12,
        FColor::Green,
        false,
        -1.0f,
        0,
        1.0f
    );
}

AOrganism* AAnimalAIController::find(TSubclassOf<AOrganism> ClassFilter,
    TArray<FString> RequiredTags,
    bool RequireAllTags,
    int MaxTrophicLevel,
    int MinTrophicLevel)
{
    if (!getModel()) return nullptr;

    bool useTrophicFilter = (MinTrophicLevel != -1 || MaxTrophicLevel != -1);
    if (useTrophicFilter)
    {
        bool classIsAnimal = ClassFilter && ClassFilter->IsChildOf(AAnimal::StaticClass());
        if (!classIsAnimal)
        {
            UE_LOG(LogTemp, Warning, TEXT("find(): TrophicLevel filter ignorado — ClassFilter não é um AAnimal."));
            useTrophicFilter = false;
        }
    }

    float radius = getModel()->getAwarenessRadius();
    float halfAngle = getModel()->getAngleVision() * 0.5f;
    FVector myLocation = getModel()->GetActorLocation();
    FVector myForward = getModel()->GetActorForwardVector();

    TSubclassOf<AOrganism> searchClass = ClassFilter ? ClassFilter : TSubclassOf<AOrganism>(AOrganism::StaticClass());

    TArray<AActor*> FoundActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // Assumindo que os peixes são Pawns

    TArray<AActor*> ToIgnore;
    ToIgnore.Add(getModel());

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        myLocation,
        radius,
        ObjectTypes,
        searchClass,
        ToIgnore,
        FoundActors
    );

    AOrganism* closest = nullptr;
    float closestDistSq = FLT_MAX;

    for (AActor* actor : FoundActors)
    {
        AOrganism* other = Cast<AOrganism>(actor);
        if (!other) continue; // Já não precisamos de "other == getModel()" porque o ToIgnore trata disso

        // A distância máxima já é garantida pelo SphereOverlapActors, portanto saltamos esse if

        // 2. Proteção do Acos com FMath::Clamp
        FVector toOther = (other->GetActorLocation() - myLocation).GetSafeNormal();
        float dotProduct = FVector::DotProduct(myForward, toOther);
        dotProduct = FMath::Clamp(dotProduct, -1.0f, 1.0f); // Evita NaN
        float angle = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

        if (angle > halfAngle) continue;

        // Filtragem de Tags
        if (RequiredTags.Num() > 0)
        {
            TArray<FString> otherTags = other->getTags();
            bool passedTagFilter = false;

            if (RequireAllTags)
            {
                passedTagFilter = true;
                for (const FString& tag : RequiredTags)
                {
                    if (!otherTags.Contains(tag))
                    {
                        passedTagFilter = false;
                        break;
                    }
                }
            }
            else
            {
                for (const FString& tag : RequiredTags)
                {
                    if (otherTags.Contains(tag))
                    {
                        passedTagFilter = true;
                        break;
                    }
                }
            }

            if (!passedTagFilter) continue;
        }

        // Filtragem de Nível Trófico
        if (useTrophicFilter)
        {
            AAnimal* otherAnimal = Cast<AAnimal>(other);
            if (!otherAnimal) continue;

            int trophic = otherAnimal->getTrophicLevel();
            if (MinTrophicLevel != -1 && trophic < MinTrophicLevel) continue;
            if (MaxTrophicLevel != -1 && trophic > MaxTrophicLevel) continue;
        }

        // Atualizar o mais próximo
        float distSq = FVector::DistSquared(myLocation, other->GetActorLocation());
        if (distSq < closestDistSq)
        {
            closestDistSq = distSq;
            closest = other;
        }
    }

    return closest;
}


void AAnimalAIController::BeginPlay()
{
    Super::BeginPlay();

}


void AAnimalAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DirectionTimer += DeltaTime;
    DetectionTimer += DeltaTime;
   
    BehaviourAnalisys(DeltaTime);
    updateMovement(DeltaTime);
    //DrawDebugVisionCone();
}


void AAnimalAIController::onTerrainCollision(FVector Normal) {
    if (!getModel()) return;

    FVector newDir = FMath::GetReflectionVector(getModel()->getTargetLocation(), Normal);

    getModel()->setTargetLocation(newDir);
}




AAnimal* AAnimalAIController::checkPredators() {

    float radius = getModel()->getAwarenessRadius();
    int trophicLevel = getModel()->getTrophicLevel();
    float angleVision = getModel()->getAngleVision();

    TArray<AActor*> FoundActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    TArray<AActor*> ToIgnore;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
    ToIgnore.Add(getModel());

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        getModel()->GetActorLocation(),
        radius,
        ObjectTypes,
        AOrganism::StaticClass(),
        ToIgnore,
        FoundActors
    );

    for (AActor* Actor : FoundActors)
    {
        AAnimal* Other = Cast<AAnimal>(Actor);
        if (!Other) continue;

        if (Other->getTrophicLevel() <= trophicLevel) continue;

        FVector direction = Other->GetActorLocation() - getModel()->GetActorLocation();
        direction.Normalize();

        FVector animalForward = getModel()->GetActorForwardVector();

        float dotProduct = FVector::DotProduct(animalForward, direction);
        float angleToOther = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

        if (angleToOther <= angleVision / 2.0f) {
            return Other;
        }
    }

    return nullptr;
}

