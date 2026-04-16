// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Fish/SharkController.h"
#include <MarineEnv/MarineEnvGameModeBase.h>

ASharkController::ASharkController()
{
}

void ASharkController::BehaviourAnalisys(float DeltaTime)
{
	Super::BehaviourAnalisys(DeltaTime);
}

void ASharkController::updateMovement(float DeltaTime)
{
    FVector CurrentLocation = getModel()->GetActorLocation();
    FVector TargetLocation = getModel()->getTargetLocation();

    FVector DesiredDirection = (TargetLocation - CurrentLocation).GetSafeNormal();

    CurrentDirection = FMath::VInterpTo(CurrentDirection, DesiredDirection, DeltaTime, getModel()->getTurnSpeed());
    CurrentDirection = CurrentDirection.GetSafeNormal();

    getModel()->AddMovementInput(CurrentDirection, getModel()->getSpeed());

    if (CurrentDirection.SizeSquared() > KINDA_SMALL_NUMBER)
    {
        FRotator TargetRotation = CurrentDirection.ToOrientationRotator();

        FRotator Smoothed = FMath::RInterpTo(
            getModel()->GetActorRotation(),
            TargetRotation,
            DeltaTime,
            3.f
        );
        getModel()->SetActorRotation(Smoothed);
    }
}

void ASharkController::roam(float DeltaTime)
{
    AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

    FVector CurrentLocation = getModel()->GetActorLocation();
    float DistToTarget = FVector::Dist(CurrentLocation, getModel()->getTargetLocation());

    if (DirectionTimer >= getModel()->getDirectionChangeInterval() || DistToTarget < 800.0f) {
        float LocationX = FMath::RandRange(-GameMode->WorldLength / 2 + 200.f, GameMode->WorldLength / 2 - 200.f);

        float LocationY = FMath::RandRange(-GameMode->WorldWidth / 2 + 200.f, GameMode->WorldWidth / 2 - 200.f);

        FVector Location = FVector(
            LocationX,
            LocationY,
            FMath::RandRange(GetTerrainZ(LocationX, LocationY), GameMode->WorldHeight)
        );
        getModel()->setTargetLocation(Location);
        DirectionTimer = 0.f;
    }
}



