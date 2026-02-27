#pragma once

#include "CoreMinimal.h"
#include "EcoClass.generated.h"


UENUM(BlueprintType)
enum class EcoClass : uint8
{
	Flora UMETA(DisplayName = "Flora"),
	Rock  UMETA(DisplayName = "Rock"),
	Prey  UMETA(DisplayName = "Prey"),
	Predator UMETA(DisplayName = "Predator"),

};