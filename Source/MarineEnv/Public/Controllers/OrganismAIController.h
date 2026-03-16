// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Entities/Organism.h"
#include "OrganismAIController.generated.h"

/**
 * 
 */




UCLASS()
class MARINEENV_API AOrganismAIController : public AAIController
{
	GENERATED_BODY()

public:
	AOrganismAIController();

	virtual AOrganism* getModel() const { return Model; }

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY()
	AOrganism* Model;

};
