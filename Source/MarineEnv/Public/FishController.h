// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
	virtual void Tick(float DeltaTime) override;

private:
	AOrganism* Organism;
	void UpdateState();
};
