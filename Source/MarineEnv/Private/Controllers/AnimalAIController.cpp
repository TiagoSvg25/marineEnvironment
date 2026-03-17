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
    // Animal = Cast<AAnimal>(InPawn);
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
            UE_LOG(LogTemp, Warning,
                TEXT("find(): TrophicLevel filter ignorado — ClassFilter não é um AAnimal."));
            useTrophicFilter = false;
        }
    }

    float radius = getModel()->getAwarenessRadius();
    float halfAngle = getModel()->getAngleVision() * 0.5f;
    FVector myLocation = getModel()->GetActorLocation();
    FVector myForward = getModel()->GetActorForwardVector();

    TSubclassOf<AOrganism> searchClass = ClassFilter ? ClassFilter : TSubclassOf<AOrganism>(AOrganism::StaticClass());

    TArray<AActor*> allActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), searchClass, allActors);

    AOrganism* closest = nullptr;
    float closestDistSq = FLT_MAX;

    for (AActor* actor : allActors)
    {
        AOrganism* other = Cast<AOrganism>(actor);
        if (!other || other == getModel()) continue;

        float distSq = FVector::DistSquared(myLocation, other->GetActorLocation());
        if (distSq > radius * radius) continue;

        FVector toOther = (other->GetActorLocation() - myLocation).GetSafeNormal();
        float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(myForward, toOther)));
        if (angle > halfAngle) continue;

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

        if (useTrophicFilter)
        {
            AAnimal* otherAnimal = Cast<AAnimal>(other);
            if (!otherAnimal) continue;

            int trophic = otherAnimal->getTrophicLevel();
            if (MinTrophicLevel != -1 && trophic < MinTrophicLevel) continue;
            if (MaxTrophicLevel != -1 && trophic > MaxTrophicLevel) continue;
        }

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
    DrawDebugVisionCone();
    BehaviourAnalisys(DeltaTime);
    AOrganism* org = find(AAnimal::StaticClass(), {"dummy"}, true, 1, 1);
    UE_LOG(LogTemp, Warning, TEXT("Found organism: %s"), org ? *org->GetName() : TEXT("None"));
    
}
