// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entities/Plant/Coral.h"
#include "Controllers/Plant/PlantAIController.h"
#include "CoralController.generated.h"

/**
 *
 */
UCLASS()
class MARINEENV_API ACoralController : public APlantAIController
{
	GENERATED_BODY()

public:
	ACoralController();

	virtual ACoral* getModel() const override { return Cast<ACoral>(Model); }


protected:

	virtual void BehaviourAnalisys(float DeltaTime) override;

	virtual void Reproduce();

};
