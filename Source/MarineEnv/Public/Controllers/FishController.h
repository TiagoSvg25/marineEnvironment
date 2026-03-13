// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OrganismAIController.h"
#include "FishController.generated.h"

/**
 * 
 */
class AOrganism;

UCLASS()
class MARINEENV_API AFishController : public AOrganismAIController
{
	GENERATED_BODY()

public:
	AFishController();

protected:
	float DirectionTimer = 0.f;

	float DetectionTimer = 0.f;

	bool isHungry = false;


	virtual void updateState() override;
	virtual AOrganism* findFood() override;
};
