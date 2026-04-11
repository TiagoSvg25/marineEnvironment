#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Terrain.generated.h"

UCLASS(Abstract) 
class MARINEENV_API ATerrain : public AActor
{
    GENERATED_BODY()

public:
    ATerrain();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    UProceduralMeshComponent* ProceduralMesh;

   
    virtual void GenerateTerrain() PURE_VIRTUAL(ATerrain::GenerateTerrain, );

protected:
    virtual void BeginPlay() override;

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector2D> UV0;
    TArray<FVector> Normals;
    TArray<FColor> Colors;
};