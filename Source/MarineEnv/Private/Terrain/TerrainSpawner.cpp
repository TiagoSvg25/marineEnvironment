#include "Terrain/TerrainSpawner.h"
#include "Terrain/TerrainRegistry.h"

ATerrainSpawner::ATerrainSpawner() {}

void ATerrainSpawner::BeginPlay()
{
    Super::BeginPlay();

    TArray<UClass*> TerrainClasses = FTerrainRegistry::GetAllTerrainClasses();

    UE_LOG(LogTemp, Warning, TEXT("=== TerrainRegistry: %d terrain(s) found ==="), TerrainClasses.Num());

    //for (UClass* Class : TerrainClasses)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Spawning: %s"), *Class->GetName());
    //    FTerrainRegistry::Spawn(Class, GetWorld(), GetActorLocation());
    //    return;
    //}

    FTerrainRegistry::Spawn(TerrainClasses.Last(), GetWorld(), GetActorLocation());
    return;

}