// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/AnimalDataAsset.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Organism.h"
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

	virtual UAnimalDataAsset* getDataAsset() const override {
		return Cast<UAnimalDataAsset>(DataAsset);;
	}





	// getters and setters

	FString getCurrentState() const;

	void setState(const FString& NewState);

	bool isHunting() const;

	void setHunting(bool NewIsHunting);

	float getEnergyThreshold() const;

	void setEnergyThreshold(float NewHungerThreshold);

	float getMaxEnergy() const;

	void setMaxEnergy(float NewMaxEnergy);

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

	float getEnergy() const;

	void setEnergy(float NewEnergy);

	float getEnergyConsumptionRate() const;

	void setEnergyConsumptionRate(float NewEnergyConsumptionRate);

	float getPerseguitionTime() const;

	void setPerseguitionTime(float NewPerseguitionTime);
	


protected:

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	FString CurrentState;

	bool Hunting = false;
};

