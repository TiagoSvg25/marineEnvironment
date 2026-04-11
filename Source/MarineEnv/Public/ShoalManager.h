// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ShoalManager.generated.h"

/**
 * 
 */

class AFish;

UCLASS()
class MARINEENV_API UShoalManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:


	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

	void AddShoal(class AFish* Shoal);

	void RemoveShoal(AFish* Fish, FString ShoalID);
	
	TMap<FString, TArray<AFish*>> GetShoals() const { return Shoals; }

private:

	TMap<FString, TArray<AFish*>> Shoals;

	int MaxShoals = 10;
};
