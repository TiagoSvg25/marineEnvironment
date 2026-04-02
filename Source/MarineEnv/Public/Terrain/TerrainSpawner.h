#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainSpawner.generated.h"

UCLASS()
class MARINEENV_API ATerrainSpawner : public AActor
{
    GENERATED_BODY()

public:
    ATerrainSpawner();

protected:
    virtual void BeginPlay() override;
};