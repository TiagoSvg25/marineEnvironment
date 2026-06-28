// Fill out your copyright notice in the Description page of Project Settings.
#include "Entities/Plant/Plant.h"
#include "Controllers/Plant/PlantAIController.h"

// Sets default values
APlant::APlant()
{
    PrimaryActorTick.bCanEverTick = true;
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




float APlant::getEnergyGainRate(){
    return EnergyGainRate;
}

void APlant::setEnergyGainRate(float NewEnergyGainRate){
    EnergyGainRate = NewEnergyGainRate;
}