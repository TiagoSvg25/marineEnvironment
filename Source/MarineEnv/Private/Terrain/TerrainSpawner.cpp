#include "Terrain/TerrainSpawner.h"
#include "Terrain/TerrainRegistry.h"

ATerrainSpawner::ATerrainSpawner() {}

void ATerrainSpawner::BeginPlay()
{
    Super::BeginPlay();

    TArray<UClass*> TerrainClasses = FTerrainRegistry::GetAllTerrainClasses();

    UE_LOG(LogTemp, Warning, TEXT("=== TerrainRegistry: %d terrain(s) found ==="), TerrainClasses.Num());

    for (UClass* Class : TerrainClasses)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawning: %s"), *Class->GetName());
           
        FVector CenteredLocation = GetActorLocation() - FVector(5000.f, 5000.f, 0.f);

        FTerrainRegistry::Spawn(Class, GetWorld(), GetActorLocation());
    }
}