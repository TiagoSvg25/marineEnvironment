#pragma once
#include "CoreMinimal.h"
#include "Terrain/Terrain.h"
#include "RockFloor.generated.h"

UCLASS()
class MARINEENV_API ARockFloor : public ATerrain
{
    GENERATED_BODY()

public:
    ARockFloor();
    virtual void GenerateTerrain() override;

protected:
    virtual void BeginPlay() override;

private:
    int32 XSize = 50;
    int32 YSize = 50;
    float Scale = 100.0f;
    float ZMultiplier = 100.0f;  // much flatter than sand
    float UVScale = 0.1f;

    void CreateVertices();
    void CreateTriangles();
};