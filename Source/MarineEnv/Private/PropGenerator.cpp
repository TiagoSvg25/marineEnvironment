#include "PropGenerator.h" 
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

APropGenerator::APropGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	// We don't create the HISM here anymore. We just create a standard root.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
}

void APropGenerator::BeginPlay()
{
	Super::BeginPlay();

	// 1. Create one HISM component for EACH mesh you added in the Blueprint
	for (int32 i = 0; i < PropMeshes.Num(); i++)
	{
		if (PropMeshes[i] != nullptr)
		{
			// Dynamically create a new HISM component
			UHierarchicalInstancedStaticMeshComponent* NewHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);

			NewHISM->SetStaticMesh(PropMeshes[i]);
			NewHISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			NewHISM->SetupAttachment(RootComponent);
			NewHISM->RegisterComponent(); // Critical when creating components at runtime!

			// Save it in our array
			HISMComponents.Add(NewHISM);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APropGenerator::GenerateProps, 1.5f, false);
}

void APropGenerator::GenerateProps()
{
	if (HISMComponents.Num() == 0) return; // Prevents crashing if you forgot to add meshes

	// We need a list of transforms for EACH HISM component
	TArray<TArray<FTransform>> TransformsPerMesh;
	TransformsPerMesh.SetNum(HISMComponents.Num());

	FVector Origin = GetActorLocation();

	for (int32 i = 0; i < NumberOfInstances; i++)
	{
		float RandX = Origin.X + FMath::RandRange(0.0f, WorldLength);
		float RandY = Origin.Y + FMath::RandRange(0.0f, WorldWidth);

		float TerrainZ = GetTerrainZ(RandX, RandY);
		float RandomScale = FMath::RandRange(MinScale, MaxScale);

		// Apply the sink offset (multiply by scale so big rocks sink further)
		float FinalZ = TerrainZ - (SinkDepth * RandomScale);

		FVector SpawnLocation = FVector(RandX, RandY, FinalZ);
		FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
		FVector SpawnScale = FVector(RandomScale);

		FTransform NewTransform(SpawnRotation, SpawnLocation, SpawnScale);

		// Pick a random rock type from your array
		int32 RandomMeshIndex = FMath::RandRange(0, HISMComponents.Num() - 1);

		// Add this transform to the specific rock type's list
		TransformsPerMesh[RandomMeshIndex].Add(NewTransform);
	}

	// Finally, add all instances to their respective HISM components efficiently
	for (int32 i = 0; i < HISMComponents.Num(); i++)
	{
		if (TransformsPerMesh[i].Num() > 0)
		{
			HISMComponents[i]->AddInstances(TransformsPerMesh[i], false);

			// ADD THIS LINE: Forces the engine to recalculate visibility bounds
			HISMComponents[i]->BuildTreeIfOutdated(true, false);
		}
	}
}

float APropGenerator::GetTerrainZ(float LocationX, float LocationY)
{
	FVector TraceStart = FVector(LocationX, LocationY, 10000.f);
	FVector TraceEnd = FVector(LocationX, LocationY, -10000.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
	{
		return Hit.ImpactPoint.Z;
	}

	return 0.f;
}