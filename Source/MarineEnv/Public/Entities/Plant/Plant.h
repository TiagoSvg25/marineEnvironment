// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Organism.h"
#include "Plant.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API APlant : public AOrganism
{
	GENERATED_BODY()

public:

	APlant();

	virtual void BeginPlay() override;

	virtual void BehaviourAnalisys() {};

	virtual void Tick(float DeltaTime) override;


	// getters and setters



protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionComponent;

	TArray<FString> Tags = { "plant" };

};
