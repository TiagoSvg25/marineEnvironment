// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Animal.h"
#include "Entities/Plant.h"
#include "Controllers/OrganismAIController.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"
#include "Components/LineBatchComponent.h"
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

	virtual void updateMovement(float DeltaTime) {}; 

	virtual void roam(float DeltaTime) {};

	virtual void HuntPrey(float DeltaTime) {} ;

	//void UpdateBehaviour() override;

	virtual AAnimal* findFood() { return nullptr;  };

	AAnimal* checkPredators();


protected:

	UPROPERTY()
	AOrganism* Target;

	UPROPERTY()
	UStaticMeshComponent* VisionConeMesh;

	UPROPERTY()
	AAnimal* Predator;


	virtual void updateState() {}

	AOrganism* find(TSubclassOf<AOrganism> ClassFilter = nullptr,
		TArray<FString> RequiredTags = {},
		bool RequireAllTags = true,
		int MaxTrophicLevel = -1,
		int MinTrophicLevel = -1);
	void DrawDebugVisionCone();

	float DirectionTimer = 10.f;

	float DetectionTimer = 10.f;

	float FleeTimer = 10.f;

	float CurrentFleeTimer = 0.f;

	
	FVector CurrentDirection;


	float InitialZ = 0.0f;
};
