#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h" // We need this to use UStaticMesh
#include "PropGenerator.generated.h" 

UCLASS()
class MARINEENV_API APropGenerator : public AActor
{
	GENERATED_BODY()

public:
	APropGenerator();

protected:
	virtual void BeginPlay() override;

	// Array of different meshes you can add in the Blueprint editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<UStaticMesh*> PropMeshes;
	
	// This will hold the HISM components we generate via code
	UPROPERTY()
	TArray<UHierarchicalInstancedStaticMeshComponent*> HISMComponents;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 NumberOfInstances = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float WorldLength = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float WorldWidth = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MinScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MaxScale = 0.8f;

	// How much the rocks sink into the terrain (multiplied by their scale)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SinkDepth = 20.0f;

	float GetTerrainZ(float LocationX, float LocationY);

	UFUNCTION()
	void GenerateProps();

	FTimerHandle SpawnTimerHandle;
};