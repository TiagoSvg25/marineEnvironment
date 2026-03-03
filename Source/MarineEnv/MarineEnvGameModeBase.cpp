// Copyright Epic Games, Inc. All Rights Reserved.



#include "MarineEnvGameModeBase.h"
#include "BaseSpawner.h"


AMarineEnvGameModeBase::AMarineEnvGameModeBase()
{
	//
}

void AMarineEnvGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	if (SpawnerClass) {
		FActorSpawnParameters SpawnParam;

		SpawnParam.Owner = this;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		Spawner = GetWorld()->SpawnActor<ABaseSpawner>(SpawnerClass.Get(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
	}
}