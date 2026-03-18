// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AnimalAIController.h"



AAnimalAIController::AAnimalAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAnimalAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn); 
    // Animal = Cast<AAnimal>(InPawn);
}


void AAnimalAIController::BeginPlay()
{
    Super::BeginPlay();

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


void AAnimalAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DirectionTimer += DeltaTime;
    DetectionTimer += DeltaTime;
    

    if(DetectionTimer > getModel()->getDirectionChangeInterval()){
        DetectionTimer = 0;
        BehaviourAnalisys(DeltaTime);
    }
    updateMovement(DeltaTime);
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

