// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementState.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class MovementState : uint8
{
	Stationary UMETA(DisplayName = "Stationary"),
	Idle UMETA(DisplayName = "Idle"),
	Hunting UMETA(DisplayName = "Hunting"),
	Fleeing UMETA(DisplayName = "Fleeing"),
	Hidden UMETA(DisplayName = "Hidden"),
	Eating UMETA(DisplayName = "Eating"),
};
