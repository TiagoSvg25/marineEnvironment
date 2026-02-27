// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpawnOrganism.h"
#include "GameFramework/GameModeBase.h"
#include "MarineEnvGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AMarineEnvGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMarineEnvGameModeBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ASpawnOrganism> SpawnerClass;

	UPROPERTY(EditAnywhere, Category = "Setup")
	ASpawnOrganism* Spawner;
	
};
