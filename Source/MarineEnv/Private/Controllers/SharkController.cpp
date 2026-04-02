// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SharkController.h"

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
        // TargetRotation.Yaw += 90.0f;
        TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch, -10.f, 10.f); 
        TargetRotation.Roll = 0.0f;

        FRotator Smoothed = FMath::RInterpTo(
            getModel()->GetActorRotation(),
            TargetRotation,
            DeltaTime,
            1.2f
        );
        getModel()->SetActorRotation(Smoothed);
    }
}

void ASharkController::roam(float DeltaTime)
{
    FVector CurrentLocation = getModel()->GetActorLocation();
    float DistToTarget = FVector::Dist(CurrentLocation, getModel()->getTargetLocation());

    if (DirectionTimer >= getModel()->getDirectionChangeInterval() || DistToTarget < 800.0f) {
        FVector RandomDir = FMath::VRand();
        RandomDir.Z *= 0.1f;
        RandomDir = RandomDir.GetSafeNormal();
        FVector NewTarget = CurrentLocation + RandomDir * FMath::RandRange(2000.0f, 4000.0f);
        if (NewTarget.Z <= 0) NewTarget.Z = FMath::Abs(NewTarget.Z);
        getModel()->setTargetLocation(NewTarget);
        DirectionTimer = 0.f;
    }
}



