// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Fish/Fish.h"
#include "SeaHorse.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API ASeaHorse : public AFish
{
	GENERATED_BODY()

public:

	ASeaHorse();

	virtual void BeginPlay() override;
	
};
