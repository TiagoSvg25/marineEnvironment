// Copyright Epic Games, Inc. All Rights Reserved.



#include "MarineEnvGameModeBase.h"



AMarineEnvGameModeBase::AMarineEnvGameModeBase()
{
	//
}

void AMarineEnvGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UMarineGameInstance* GI = Cast<UMarineGameInstance>(GetGameInstance());

	if (GI)
	{
		WorldLength = GI->MapSize;
		WorldWidth = GI->MapSize;
		UE_LOG(LogTemp, Warning, TEXT("MapSize loaded from GameInstance: %f"), GI->MapSize);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance cast failed!"));
	}

	/*

	if (SpawnerClass) {
		FActorSpawnParameters SpawnParam;

		SpawnParam.Owner = this;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		Spawner = GetWorld()->SpawnActor<ABaseSpawner>(SpawnerClass.Get(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
	}*/
}