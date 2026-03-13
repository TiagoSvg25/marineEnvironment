// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/OrganismDataAsset.h"
#include "Entities/Organism.h"
#include "GameFramework/Actor.h"
#include "SpawnOrganism.generated.h"

UCLASS()
class MARINEENV_API ASpawnOrganism : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnOrganism();


	void SpawnOrganism(UOrganismDataAsset* OrganismData);

	void setSpawnRestrictions(double width, double lenght, double height, int entityLimit, TArray<UOrganismDataAsset*> OrganismList);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<UOrganismDataAsset*> OrganismList;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int entityLimit = 10;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	double width = 200;
	 
	UPROPERTY(EditAnywhere, Category = "Spawn")
	double height = 200;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	double length = 500;

	int spawnCount = 0;


};

