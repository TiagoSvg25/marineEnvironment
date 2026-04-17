#include "Controllers/ShoalManager.h"
#include "Entities/Fish/Fish.h"

void UShoalManager::Initialize(FSubsystemCollectionBase& Collection) {}

void UShoalManager::Deinitialize()
{
    Shoals.Empty();
}

void UShoalManager::AddShoal(AFish* Fish)
{
    if (!Fish) return;

    FString speciesName = Fish->GetClass()->GetName();

    for (auto& pair : Shoals) {
        if (pair.Key.StartsWith(speciesName) && pair.Value.Num() < MaxShoals) {
            pair.Value.Add(Fish);
            Fish->setShoalId(pair.Key);

            MergeShoals();
            return;
        }
    }

    FString newKey = FString::Printf(TEXT("%s_Shoal_%d"), *speciesName, Shoals.Num());
    Shoals.Add(newKey, TArray<AFish*>{Fish});
    Fish->setShoalId(newKey);
    MergeShoals();
}

void UShoalManager::RemoveShoal(AFish* Fish, FString ShoalID)
{
    if (!Fish || !Shoals.Contains(ShoalID)) return;

    Shoals[ShoalID].Remove(Fish);

    if (Shoals[ShoalID].Num() == 0) {
        Shoals.Remove(ShoalID);
        return;
    }
}

void UShoalManager::MergeShoals()
{
    TArray<FString> Keys;
    Shoals.GetKeys(Keys);

    for (int i = 0; i < Keys.Num(); i++) {
        for (int j = i + 1; j < Keys.Num(); j++) {
            FString KeyA = Keys[i];
            FString KeyB = Keys[j];

            if (!Shoals.Contains(KeyA) || !Shoals.Contains(KeyB)) continue;

            FString SpeciesA = KeyA.Left(KeyA.Find(TEXT("_Shoal_")));
            FString SpeciesB = KeyB.Left(KeyB.Find(TEXT("_Shoal_")));
            if (SpeciesA != SpeciesB) continue;

            if (Shoals[KeyA].Num() + Shoals[KeyB].Num() > MaxShoals) continue;

            FVector CenterA = FVector::ZeroVector;
            for (AFish* f : Shoals[KeyA]) CenterA += f->GetActorLocation();
            CenterA /= Shoals[KeyA].Num();

            FVector CenterB = FVector::ZeroVector;
            for (AFish* f : Shoals[KeyB]) CenterB += f->GetActorLocation();
            CenterB /= Shoals[KeyB].Num();

            if (FVector::Dist(CenterA, CenterB) <= MinShoalDistance) {
                for (AFish* f : Shoals[KeyB]) {
                    f->setShoalId(KeyA);
                    Shoals[KeyA].Add(f);
                }

                
                Shoals.Remove(KeyB);
            }
        }
    }
}