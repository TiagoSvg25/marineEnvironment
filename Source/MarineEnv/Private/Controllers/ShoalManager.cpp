// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ShoalManager.h"
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

			TArray<AFish*> neighborsWithoutSelf = pair.Value;

			neighborsWithoutSelf.Remove(Fish);

			Fish->setNeighbors(neighborsWithoutSelf);

			for (AFish* member : pair.Value)
			{
				if (member == Fish) continue;

				TArray<AFish*> memberNeighbors = pair.Value;
				memberNeighbors.Remove(member);
				member->setNeighbors(memberNeighbors);

			}
		
			MergeShoals();
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

	MergeShoals();


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


void UShoalManager::MergeShoals()
{
	TArray<FString> Keys;
	Shoals.GetKeys(Keys);

	for (int i = 0; i < Keys.Num(); i++)
	{
		for (int j = i + 1; j < Keys.Num(); j++)
		{
			FString KeyA = Keys[i];
			FString KeyB = Keys[j];

			if (!Shoals.Contains(KeyA) || !Shoals.Contains(KeyB)) continue;

			FString SpeciesA = KeyA.Left(KeyA.Find(TEXT("_Shoal_")));
			FString SpeciesB = KeyB.Left(KeyB.Find(TEXT("_Shoal_")));
			if (SpeciesA != SpeciesB) continue;

			if (Shoals[KeyA].Num() + Shoals[KeyB].Num() > MaxShoals) continue;

			FVector CenterA = FVector::ZeroVector;
			for (AFish* Fish : Shoals[KeyA])
				CenterA += Fish->GetActorLocation();
			CenterA /= Shoals[KeyA].Num();

			FVector CenterB = FVector::ZeroVector;
			for (AFish* Fish : Shoals[KeyB])
				CenterB += Fish->GetActorLocation();
			CenterB /= Shoals[KeyB].Num();

			if (FVector::Dist(CenterA, CenterB) <= MinShoalDistance)
			{
				for (AFish* Fish : Shoals[KeyB])
				{
					Fish->setShoalId(KeyA);
					Shoals[KeyA].Add(Fish);
				}

				for (AFish* Fish : Shoals[KeyA])
					Fish->setNeighbors(Shoals[KeyA]);

				Shoals.Remove(KeyB);
			}
		}
	}
}