// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Controllers/AnimalAIController.h"
#include "Entities/HerbFish.h"
#include "Entities/Plant.h"
#include "HerbFishController.generated.h"

/**
 *
 */


UCLASS()
class MARINEENV_API AHerbFishController : public AAnimalAIController
{
	GENERATED_BODY()

public:
	AHerbFishController();

	virtual AHerbFish* getModel() const override { return Cast<AHerbFish>(Model); }


protected:

	virtual void BehaviourAnalisys(float DeltaTime) override;

	virtual void HuntPrey(float DeltaTime) override;

	virtual void updateMovement(float DeltaTime) override;

	virtual void roam(float DeltaTime) override;

	//virtual void updateState() override;
	virtual APlant* findPlant();
};

