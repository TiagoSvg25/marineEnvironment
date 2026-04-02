// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FishController.h"
#include "SharkController.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API ASharkController : public AFishController
{
	GENERATED_BODY()

public:
    ASharkController();

protected:
    virtual void BehaviourAnalisys(float DeltaTime) override;
    virtual void updateMovement(float DeltaTime) override;
    virtual void roam(float DeltaTime) override;

private:
    FString PreviousState;
	
};
