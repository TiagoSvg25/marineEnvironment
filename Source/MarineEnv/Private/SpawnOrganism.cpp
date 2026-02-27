// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnOrganism.h"

// Sets default values
ASpawnOrganism::ASpawnOrganism()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnOrganism::BeginPlay()
{
	Super::BeginPlay();
	SpawnOrganism();
	
}

void ASpawnOrganism::SpawnOrganism()
{
	if (!OrganismData) return;

	FVector SpawnLocation = FVector(10.0f, 30.0f, 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;
	FTransform Transform(Rotation, SpawnLocation);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	AOrganism* Organism = GetWorld()->SpawnActor<AOrganism>(AOrganism::StaticClass(), Transform, SpawnParam);

	if (Organism)
	{
		fill_information(OrganismData, Organism);
	}
}

void ASpawnOrganism::fill_information(UOrganismDataAsset* OrganismDat, AOrganism* Organism)
{
	Organism->setEnvironmentalCharacteristics(OrganismDat->Environmental.EcoType, OrganismDat->Environmental.MinDepth, OrganismDat->Environmental.MaxDepth);
	Organism->setPhysicalCharacteristics(OrganismDat->Physical.Size, OrganismDat->Physical.Height, OrganismDat->Physical.Weight);
	Organism->setMovementCharacteristics(OrganismDat->Movement.Speed, OrganismDat->Movement.AwarenessRadius, OrganismDat->Movement.AngleVision);
	Organism->setOrganismMeshe(OrganismDat->Mesh);
}
