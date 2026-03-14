// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/AnimalDataAsset.h"
#include "Organism.h"
#include "Animal.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MARINEENV_API AAnimal : public AOrganism
{
	GENERATED_BODY()

public:

	AAnimal();

	virtual void BeginPlay() override;

	virtual void updateMovement(float DeltaTime) {};

	virtual void BehaviourAnalisys() {};

	virtual void UpdateBehaviour() {};

	virtual void Tick(float DeltaTime) override;


	FString getCurrentState() const { return CurrentState; };

	void setState(const FString& NewState) { CurrentState = NewState; };



	UPROPERTY(EditAnywhere, Category = "Data")
	UAnimalDataAsset* AnimalDataAsset;


private:

	FString CurrentState;

};

