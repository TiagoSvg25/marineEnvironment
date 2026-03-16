// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Animal.h"
#include "Controllers/OrganismAIController.h"
#include "AnimalAIController.generated.h"

/**
 * 
 */
UCLASS()

class MARINEENV_API AAnimalAIController : public AOrganismAIController
{
	GENERATED_BODY()

public:

	AAnimalAIController();


	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual AAnimal* getModel() const override { return Cast<AAnimal>(Model); }

	//void setPredatorNearby(AOrganism* InPredator);

	//bool checkEscape(AOrganism* Prey, AOrganism* InPredator);

	//void onActorCollision(AOrganism* Collided);

	//void onTerrainCollision(FVector Normal);

	virtual void BehaviourAnalisys(float DeltaTime) {};


	virtual void updateMovement(float DeltaTime, FVector TargetLocation) {};




	//virtual void HuntPrey() {} ;

	//void UpdateBehaviour() override;


protected:

	UPROPERTY()
	AOrganism* Target;


	UPROPERTY()
	AOrganism* Predator;

	virtual void updateState() {};
	virtual AOrganism* findFood() { return nullptr; }

	float DirectionTimer;
	
};
