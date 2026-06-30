// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Plant/PlantAIController.h"

APlantAIController::APlantAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlantAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (!getModel()) return;

    getModel()->setState("Idle");

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [this]()
        {
            if (!IsValid(getModel())) return;

            FVector CurLoc = getModel()->GetActorLocation();
            SnapToFloor(CurLoc);
            getModel()->SetActorLocation(CurLoc);
            UE_LOG(LogTemp, Display, TEXT("Clamped to %s"), *CurLoc.ToString());

        }, 0.1f, false);
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

