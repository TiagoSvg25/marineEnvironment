// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganismDataAsset.h"
#include "AnimalDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API UAnimalDataAsset : public UOrganismDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DirectionChangeInterval;


	UPROPERTY(EditAnywhere, Category = "Energy")
	float Energy = 100.0f;

	UPROPERTY(EditAnywhere, Category="Energy")
	float EnergyThreshold = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Energy")
	float MaxEnergy = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Energy")
	float EnergyConsumptionRate = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Awareness")
	float AwarenessRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Awareness")
	float AngleVision = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Nature")
	int TrophicLevel = 1;

	UPROPERTY(EditAnywhere, Category = "States")
	FString CurrentState = "Idle";

	/*UPROPERTY(EditAnywhere, Category = "States")
	TArray<FString> States = { "Idle", "Hunting", "Fleeing", "Reproduction", "Hungry" };
	*/
};



