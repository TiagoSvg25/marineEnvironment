#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarineGameInstance.h"
#include "Terrain.h"
#include "TerrainSpawner.generated.h"

UCLASS()
class MARINEENV_API ATerrainSpawner : public AActor
{
    GENERATED_BODY()

public:
    ATerrainSpawner();

protected:

    UPROPERTY(EditAnywhere, Category = "Terrain")
    TSubclassOf<ATerrain> TerrainClass;

    virtual void BeginPlay() override;
};