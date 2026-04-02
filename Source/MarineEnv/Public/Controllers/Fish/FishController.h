// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Controllers/AnimalAIController.h"
#include "Entities/Fish/Fish.h"
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
	
	virtual void BehaviourAnalisys(float DeltaTime) override;


	virtual void HuntPrey(float DeltaTime) override;

	virtual void updateMovement(float DeltaTime) override;

	virtual void roam(float DeltaTime) override;

	virtual void onActorCollision(AOrganism* Collided) override;


	void Reproduce();

	//virtual void updateState() override;


};
