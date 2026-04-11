// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Fish/FishController.h"
#include "FlockingController.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AFlockingController : public AFishController
{
	GENERATED_BODY()
	
public:

	AFlockingController();

	void BehaviourAnalisys(float DeltaTime) override;

	void flockingBehaviour();
	
	void alignWithNeighbors();

	void cohesionWithNeighbors();

	void separateFromNeighbors();

private:

	FVector AlignmentVector;

	FVector CohesionVector;

	FVector SeparationVector;

	float SeparationDistance = 40.0f;


};
