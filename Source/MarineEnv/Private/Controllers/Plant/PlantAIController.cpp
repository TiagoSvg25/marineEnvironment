// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Plant/PlantAIController.h"

APlantAIController::APlantAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlantAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (getModel()) {
        getModel()->setState("Idle");
        FVector curLoc = getModel()->GetActorLocation();
        SnapToFloor(curLoc);
        getModel()->SetActorLocation(curLoc);
        UE_LOG(LogTemp, Display, TEXT("Clamped to %s"), *curLoc.ToString());
    }

}


void APlantAIController::BeginPlay()
{
    Super::BeginPlay();

    //InitialZ = getModel()->GetActorLocation().Z;
}


void APlantAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    BehaviourAnalisys(DeltaTime);
}

