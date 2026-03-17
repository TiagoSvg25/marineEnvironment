// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AnimalAIController.h"



AAnimalAIController::AAnimalAIController()
{

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

    CurrentDirection = FMath::VRand();
    FVector2D Random2D = FMath::RandPointInCircle(1.0f);

    TargetLocation = FVector(Random2D.X, Random2D.Y, 0.0f) * 1000.0f;


    TargetLocation.Z = InitialZ;

}


void AAnimalAIController::Tick(float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("AnimalAIController Tick"));
    Super::Tick(DeltaTime);

    DirectionTimer += DeltaTime;

    BehaviourAnalisys(DeltaTime);

}
