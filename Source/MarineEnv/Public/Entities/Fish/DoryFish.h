// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Fish/Fish.h"
#include "DoryFish.generated.h"

UCLASS()
class MARINEENV_API ADoryFish : public AFish
{
	GENERATED_BODY()
	
public:

	ADoryFish();

	virtual void BeginPlay() override;
};
