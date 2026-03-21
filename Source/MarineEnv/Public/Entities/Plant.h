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

	FString getCurrentState() const;

	void setState(const FString& NewState);

	float getEnergy() const;

	void setEnergy(float NewEnergy);

	float getSpawnRadius() const;

	void setSpawnRadius(float NewSpawnRadius);


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plant | Stats")
	FString CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plant | Stats")
	float CurrentEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plant | Stats")
	float SpawnRadius;
	
};
