#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h" 
#include "PropGenerator.generated.h" 

UCLASS()
class MARINEENV_API APropGenerator : public AActor
{
	GENERATED_BODY()

public:
	APropGenerator();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<UStaticMesh*> PropMeshes;
	
	UPROPERTY()
	TArray<UHierarchicalInstancedStaticMeshComponent*> HISMComponents;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bEnableCollision = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int NumberOfInstances = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MinScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MaxScale = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SinkDepth = 20.0f;

	float GetTerrainZ(float LocationX, float LocationY);

	UFUNCTION()
	void GenerateProps();

	FTimerHandle SpawnTimerHandle;
};