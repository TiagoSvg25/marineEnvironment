// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlantAIController.h"

APlantAIController::APlantAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlantAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    // Plant = Cast<AAnimal>(InPawn);
}


void APlantAIController::BeginPlay()
{
    Super::BeginPlay();

    //InitialZ = getModel()->GetActorLocation().Z;
    if (getModel()) {
        getModel()->setState("Idle");
    }
}


void APlantAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    BehaviourAnalisys(DeltaTime);
}