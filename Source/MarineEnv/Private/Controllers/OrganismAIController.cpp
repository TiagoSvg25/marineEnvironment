// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/OrganismAIController.h"
#include "Entities/Organism.h"
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

/*
void AOrganismAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    Organism = Cast<AOrganism>(InPawn);
}


void AOrganismAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (!Organism) return;

    DirectionTimer += DeltaTime;
    DetectionTimer += DeltaTime;

    if (DetectionTimer >= Organism->DetectionInterval)
    {
        DetectionTimer = 0.0f;
        updateState();
    }
    Organism->updateMovement(DeltaTime);
}

void AOrganismAIController::setPredatorNearby(AOrganism* InPredator)
{
    Predator = InPredator;
    if (Organism)
        Organism->setState(OrganismState::Fleeing);
}

bool AOrganismAIController::checkEscape(AOrganism* Prey, AOrganism* InPredator) {

    if(!InPredator || !Prey) return true;
        
    float distance = FVector::DistSquared(Prey->GetActorLocation(), InPredator->GetActorLocation());
    UE_LOG(LogTemp, Warning, TEXT("Distance: %f, AWare: %f"), FMath::Sqrt(distance), InPredator->getMovementCharacteristics().AwarenessRadius);
    return FMath::Sqrt(distance) > InPredator->getMovementCharacteristics().AwarenessRadius;
}

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
