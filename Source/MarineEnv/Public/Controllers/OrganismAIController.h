// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OrganismAIController.generated.h"

/**
 * 
 */

class AOrganism;


UCLASS()
class MARINEENV_API AOrganismAIController : public AAIController
{
	GENERATED_BODY()

public:
	AOrganismAIController();

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	void setPredatorNearby(AOrganism* InPredator);

	bool checkEscape(AOrganism* Prey, AOrganism* InPredator);

	void onActorCollision(AOrganism* Collided);

	void onTerrainCollision(FVector Normal);



protected:
	UPROPERTY()
	AOrganism* Organism;

	UPROPERTY()
	AOrganism* Target;

	UPROPERTY()
	AOrganism* Predator;

	float DirectionTimer;

	float DetectionTimer;

	bool isHungry = false;


	virtual void updateState() {};
	virtual AOrganism* findFood() { return nullptr; }

};
