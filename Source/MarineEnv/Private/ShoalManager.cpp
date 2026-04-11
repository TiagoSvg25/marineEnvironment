// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoalManager.h"
#include "Entities/Fish/Fish.h"


void UShoalManager::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UShoalManager::Deinitialize()
{
	Shoals.Empty();
}

void UShoalManager::AddShoal(AFish* Fish)
{
	if (Fish == nullptr) {
		return;
	}
	
	FString speciesName = Fish->GetClass()->GetName();

	for (auto& pair : Shoals) {
		if (pair.Key.StartsWith(speciesName) && pair.Value.Num() < MaxShoals) {
			pair.Value.Add(Fish);

			Fish->setShoalId(pair.Key);
			Fish->setNeighbors(pair.Value);
			
			for (AFish* member : pair.Value)
			{
				member->setNeighbors(pair.Value);
			}
			return;
		}
	}

	FString newKey = FString::Printf(TEXT("%s_Shoal_%d"), *speciesName, Shoals.Num());

	Shoals.Add(newKey, TArray<AFish*>{Fish});

	Fish->setShoalId(newKey);
	Fish->setNeighbors(Shoals[newKey]);


	for (AFish* member : Shoals[newKey])
	{
		member->setNeighbors(Shoals[newKey]);
	}

}

void UShoalManager::RemoveShoal(AFish* Fish, FString ShoalID)
{
	if (Fish == nullptr) {
		return;
	}
	
	if (Shoals.Contains(ShoalID)) {
		Shoals[ShoalID].Remove(Fish);

		if (Shoals[ShoalID].Num() == 0) {
			Shoals.Remove(ShoalID);
			return;
		}

		for (AFish* member : Shoals[ShoalID])
			member->setNeighbors(Shoals[ShoalID]);

	}
}


