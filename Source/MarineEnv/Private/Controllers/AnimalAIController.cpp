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
    UE_LOG(LogTemp, Warning, TEXT("AnimalAIController Tick"));
    Super::Tick(DeltaTime);

    DirectionTimer += DeltaTime;


    BehaviourAnalisys(DeltaTime);
    updateMovement(DeltaTime);
}
