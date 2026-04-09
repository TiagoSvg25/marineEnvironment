// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Organism.h"
#include "Components/SphereComponent.h"
#include "Animal.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MARINEENV_API AAnimal : public AOrganism
{
	GENERATED_BODY()

public:

	AAnimal();

	virtual void BeginPlay() override;

	virtual void updateMovement(float DeltaTime) {};

	virtual void BehaviourAnalisys() {};

	virtual void UpdateBehaviour() {};

	virtual void Tick(float DeltaTime) override;





	// getters and setters


	float getBaseSpeed() const;

	void setBaseSpeed(float NewSpeed);


	float getAwarenessRadius() const;

	void setAwarenessRadius(float NewAwarenessRadius);

	float getAngleVision() const;

	void setAngleVision(float NewAngleVision);

	int getTrophicLevel() const;

	void setTrophicLevel(int NewTrophicLevel);

	float getDirectionChangeInterval() const;

	void setDirectionChangeInterval(float NewDirectionChangeInterval);

	float getSpeed() const;

	void setSpeed(float NewSpeed);

	float getTurnSpeed() const;

	void setTurnSpeed(float NewTurnSpeed);

	void setTargetLocation(FVector location);

	FVector getTargetLocation();



protected:

	FVector CurrentTargetLocation;
	float Speed = 0.5f;
	float BaseSpeed = 0.5f;
	float DirectionChangeInterval;

	float AwarenessRadius = 1000.0f;
	float AngleVision = 45.0f;
	int TrophicLevel = 1;
	int TurnSpeed = 2.0f;
	UFloatingPawnMovement* FloatingMovement;

};

	