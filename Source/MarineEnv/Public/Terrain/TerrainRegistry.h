#pragma once
#include "CoreMinimal.h"
#include "Terrain.h"

class MARINEENV_API FTerrainRegistry
{
public:
    // Returns all classes that inherit from ATerrain
    static TArray<UClass*> GetAllTerrainClasses();

    // Spawns a terrain by class
    static ATerrain* Spawn(UClass* TerrainClass, UWorld* World, FVector Location);
};