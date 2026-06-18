#include "Terrain/TerrainSpawner.h"
#include "Terrain/TerrainRegistry.h"

ATerrainSpawner::ATerrainSpawner() {}

void ATerrainSpawner::BeginPlay()
{
    Super::BeginPlay();

    TArray<UClass*> TerrainClasses = FTerrainRegistry::GetAllTerrainClasses();

    UMarineGameInstance* GI = Cast<UMarineGameInstance>(GetGameInstance());

    UE_LOG(LogTemp, Warning, TEXT("=== TerrainRegistry: %d terrain(s) found ==="), TerrainClasses.Num());

    for (UClass* Class : TerrainClasses)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawning: %s"), *Class->GetName());
           
        FVector CenteredLocation = GetActorLocation() - FVector(GI->MapSize, GI->MapSize,0.f);

        FTerrainRegistry::Spawn(Class, GetWorld(), GetActorLocation());
    }
}