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
	float Size = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
	float Height = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
	float Weight = 0.f;

};


USTRUCT(BlueprintType)
struct FEnvironmentalCharacteristics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	EcoClass EcoType = EcoClass::Flora;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	float MinDepth = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	float MaxDepth = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental")
	int TrophicLevel;
};

USTRUCT(BlueprintType)
struct FMovementCharacteristics
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	MovementState InitialState = MovementState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AwarenessRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AngleVision = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed = 0.f;
};


