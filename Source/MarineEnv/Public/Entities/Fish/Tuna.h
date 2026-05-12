// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Fish/Fish.h"
#include "Tuna.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API ATuna : public AFish
{
	GENERATED_BODY()
	
public:

	ATuna();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
