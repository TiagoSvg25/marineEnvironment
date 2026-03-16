// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Controllers/AnimalAIController.h"
#include "Entities/Fish.h"
#include "FishController.generated.h"

/**
 * 
 */


UCLASS()
class MARINEENV_API AFishController : public AAnimalAIController
{
	GENERATED_BODY()

public:
	AFishController();

	virtual AFish* getModel() const override { return Cast<AFish>(Model); }
	

protected:
	/*float DirectionTimer = 0.f;

	float DetectionTimer = 0.f;

	bool isHungry = false;
	*/
	virtual void BehaviourAnalisys(float DeltaTime) override;

	//virtual void HuntPrey() override;

	virtual void updateMovement(float DeltaTime, FVector TargetLocation) override;
	

	//virtual void updateState() override;
	//virtual AOrganism* findFood() override;

};
