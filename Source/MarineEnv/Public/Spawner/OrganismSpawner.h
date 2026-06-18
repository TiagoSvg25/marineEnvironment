// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entities/Organism.h"
#include <MarineEnv/MarineEnvGameModeBase.h>
#include "MarineGameInstance.h"
#include "OrganismSpawner.generated.h"

UCLASS()
class MARINEENV_API AOrganismSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrganismSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "World");
	TMap<TSubclassOf<AOrganism>, int32> spawnCounts;

	void Spawn(UClass* OrganismClass, UWorld* World);

	float GetTerrainZ(float LocationX, float LocationY);

};
