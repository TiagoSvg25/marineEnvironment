// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fish.h"
#include "ClownFish.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AClownFish : public AFish
{
	GENERATED_BODY()

public:

	AClownFish();

	virtual void BeginPlay() override;

};

