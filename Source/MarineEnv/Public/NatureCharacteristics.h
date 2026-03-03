// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EcoClass.h"
#include "MovementState.h"
#include "NatureCharacteristics.generated.h"



USTRUCT(BlueprintType)
struct FPhysicalCharacteristics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
	float Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
	float Weight;

};


USTRUCT(BlueprintType)
struct FEnvironmentalCharacteristics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	EcoClass EcoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	int TrophicLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	float MinDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	float MaxDepth;
};

USTRUCT(BlueprintType)
struct FMovementCharacteristics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	MovementState InitialState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AwarenessRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AngleVision;
};


