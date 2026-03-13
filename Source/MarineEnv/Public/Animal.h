// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimalDataAsset.h"
#include "Organism.h"
#include "Animal.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AAnimal : public AOrganism
{
	GENERATED_BODY()

public:

	void BeginPlay();

	virtual void updateMovement(float DeltaTime);

	virtual void BehaviourAnalisys();

	virtual void UpdateBehaviour();


	UAnimalDataAsset* AnimalDataAsset;

	UOrganismDataAsset* OrganismDataAsset;
};

