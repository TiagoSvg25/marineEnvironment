// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "Algae.generated.h"

/**
 * */
UCLASS()
class MARINEENV_API AAlgae : public APlant
{
	GENERATED_BODY()

public:

	AAlgae();

	~AAlgae();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bIsPredator = false;

};