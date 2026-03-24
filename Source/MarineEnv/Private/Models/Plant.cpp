// Fill out your copyright notice in the Description page of Project Settings.
#include "Entities/Plant.h"
#include "Controllers/PlantAIController.h"

// Sets default values
APlant::APlant()
{
    PrimaryActorTick.bCanEverTick = true;
    DataAsset = CreateDefaultSubobject<UOrganismDataAsset>(TEXT("PlantDataAsset"));
    /*AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAnimalAIController::StaticClass();*/
}

void APlant::BeginPlay()
{
    Super::BeginPlay();
}

void APlant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// --- Getters and Setters ---

FString APlant::getCurrentState() const
{
    return CurrentState;
}

void APlant::setState(const FString& NewState)
{
    CurrentState = NewState;
}

float APlant::getEnergy() const
{
    return CurrentEnergy;
}

void APlant::setEnergy(float NewEnergy)
{
    CurrentEnergy = NewEnergy;
}