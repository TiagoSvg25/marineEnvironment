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
