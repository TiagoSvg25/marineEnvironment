#include "Terrain/TerrainRegistry.h"

TArray<UClass*> FTerrainRegistry::GetAllTerrainClasses()
{
    TArray<UClass*> Result;
    GetDerivedClasses(ATerrain::StaticClass(), Result, true);
    return Result;
}

ATerrain* FTerrainRegistry::Spawn(UClass* TerrainClass, UWorld* World, FVector Location)
{
    if (!TerrainClass || !World) return nullptr;
    return World->SpawnActor<ATerrain>(TerrainClass, Location, FRotator::ZeroRotator);
}