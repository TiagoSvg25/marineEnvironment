// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Entities/Fish/Fish.h"
#include "Sardine.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API ASardine : public AFish
{
	GENERATED_BODY()

public:
	ASardine();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
