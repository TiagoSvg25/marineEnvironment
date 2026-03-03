// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MarineEnvGameModeBase.generated.h"

/**
 * 
 */
class ABaseSpawner;
UCLASS()
class MARINEENV_API AMarineEnvGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMarineEnvGameModeBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ABaseSpawner> SpawnerClass;

	UPROPERTY(EditAnywhere, Category = "Setup")
	ABaseSpawner* Spawner;
	
};
