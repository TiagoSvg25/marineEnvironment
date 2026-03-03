#pragma once

#include "CoreMinimal.h"
#include "EcoClass.generated.h"


UENUM(BlueprintType)
enum class EcoClass : uint8
{
	Flora UMETA(DisplayName = "Flora"),
	Sctruture  UMETA(DisplayName = "Sctruture"),
	Animal  UMETA(DisplayName = "Animal"),
};

