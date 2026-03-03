// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganismDataAsset.h"
#include "Organism.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

UCLASS()
class MARINEENV_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TArray<UOrganismDataAsset*> OrganismList;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	int entityLimit = 20;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	double width = 2000;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	double height = 1000;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	double length = 2000;

};
