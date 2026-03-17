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


    CurrentDirection = FMath::VRand();

    TargetLocation = FMath::VRand();

}


void AAnimalAIController::Tick(float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("AnimalAIController Tick"));
    Super::Tick(DeltaTime);

    DirectionTimer += DeltaTime;

    BehaviourAnalisys(DeltaTime);

}
