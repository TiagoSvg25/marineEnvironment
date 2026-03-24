// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entities/Algae.h"
#include "Controllers/PlantAIController.h"
#include "AlgaeController.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AAlgaeController : public APlantAIController
{
	GENERATED_BODY()

public:
	AAlgaeController();

	virtual AAlgae* getModel() const override { return Cast<AAlgae>(Model); }


protected:

	virtual void BehaviourAnalisys(float DeltaTime) override;

	virtual void Reproduce();
	
};
