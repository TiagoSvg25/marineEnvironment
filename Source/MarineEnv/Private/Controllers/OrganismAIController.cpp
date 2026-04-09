// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/OrganismAIController.h"
#include "Entities/Organism.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>


AOrganismAIController::AOrganismAIController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}

void AOrganismAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AOrganismAIController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);
    Model = Cast<AOrganism>(InPawn);
}


void AOrganismAIController::SnapToFloor(FVector& Location)
{
    FVector Start = Location + FVector(0, 0, 500.f); // trace from above
    FVector End = Location - FVector(0, 0, 10000.f); // trace downward

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(getModel());

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params))
    {
        Location = Hit.ImpactPoint;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s could not snap to floor"), *GetName());
    }
}




float AOrganismAIController::GetTerrainZ(float LocationX, float LocationY) {
    FVector TraceStart = FVector(LocationX, LocationY, 10000.f);
    FVector TraceEnd = FVector(LocationX, LocationY, -10000.f);

    FHitResult Hit;
    FCollisionQueryParams Params;

    if (getModel()->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
    {
        return Hit.ImpactPoint.Z;
    }

    return 0.f;
}

/*

void AOrganismAIController::onActorCollision(AOrganism* Collided) {

    if(!Target) return;
    if(Collided != Target) return;

    isHungry = false;
    Organism->setState(OrganismState::Idle);
    Collided->Destroy();
    Target = nullptr;
    UE_LOG(LogTemp, Warning, TEXT("Caught prey!"));

    return;
}

void AOrganismAIController::onTerrainCollision(FVector Normal) {
    if (!Organism) return;

    FVector newDir = FMath::GetReflectionVector(Organism->CurrentDirection,Normal);

    Organism->TargetDirection = newDir.GetSafeNormal();
}

*/
