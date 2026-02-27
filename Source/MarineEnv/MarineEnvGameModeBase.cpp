// Copyright Epic Games, Inc. All Rights Reserved.


#include "MarineEnvGameModeBase.h"

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

		Spawner = GetWorld()->SpawnActor<ASpawnOrganism>(SpawnerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
	}
}