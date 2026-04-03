// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/OrganismAIController.h"
#include "Entities/Plant/Plant.h"
#include "PlantAIController.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API APlantAIController : public AOrganismAIController
{
	GENERATED_BODY()

public:

	APlantAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual APlant* getModel() const override { return Cast<APlant>(Model); }

	virtual void BehaviourAnalisys(float DeltaTime) {};


protected:

	virtual void updateState() {};

	float InitialZ = 0.0f;
	
};
