#include "Terrain/SandFloor.h"
#include <MarineEnv/MarineEnvGameModeBase.h>
#include "KismetProceduralMeshLibrary.h"


ASandFloor::ASandFloor()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFinder(
		TEXT("/Game/MyTexture.MyTexture")
	);

	if (MatFinder.Succeeded())
	{
		TerrainMaterial = MatFinder.Object;
	}
}
void ASandFloor::BeginPlay()
{
	Super::BeginPlay();
	AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

	setScale(GameMode->WorldLength/getXSize());
	GenerateTerrain();
}

void ASandFloor::GenerateTerrain()
{
	if (!ProceduralMesh) return;

	Vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	Normals.Empty();
	Colors.Empty();
	ProceduralMesh->ClearMeshSection(0);

	CreateSandVertices();
	CreateSandTriangles();

	TArray<FProcMeshTangent> Tangents;
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProceduralMesh->CreateMeshSection(
		0,
		Vertices,
		Triangles,
		Normals,
		UV0,
		Colors,
		Tangents,
		true
	);

	if (getTerrainMaterial())
	{
		ProceduralMesh->SetMaterial(0, getTerrainMaterial());
	}
}

void ASandFloor::CreateSandVertices()
{
	float MaxDepth = 0.0f;
	float MinDepth = getZMultiplier();

	for (int32 X = 0; X <= getXSize(); ++X)
	{
		for (int32 Y = -getYSize()/2; Y <= getYSize()/2; ++Y)
		{
			FVector2D NoiseInput = FVector2D(X + 0.1f + getSeed(), Y + 0.1f + getSeed()) * getPerlinScale();

			float NoiseValue = FMath::PerlinNoise2D(NoiseInput);
			float Z = (NoiseValue + 1.0f) * getZMultiplier();

			Vertices.Add(FVector(X * getScale(), Y * getScale(), Z));
			UV0.Add(FVector2D(X * getUVScale(), Y * getUVScale()));

			float Alpha = FMath::GetMappedRangeValueClamped(FVector2D(MaxDepth, MinDepth), FVector2D(0.2f, 1.0f), Z);
			uint8 Brightness = static_cast<uint8>(Alpha * 255);
			Colors.Add(FColor(Brightness, Brightness, Brightness, 255));
		}
	}
}

void ASandFloor::CreateSandTriangles()
{
	for (int32 X = 0; X < getXSize(); ++X)
	{
		for (int32 Y = 0; Y < getYSize(); ++Y)
		{
			int32 BottomLeft = (X * (getYSize() + 1)) + Y;
			int32 BottomRight = ((X + 1) * (getYSize() + 1)) + Y;
			int32 TopLeft = (X * (getYSize() + 1)) + (Y + 1);
			int32 TopRight = ((X + 1) * (getYSize() + 1)) + (Y + 1);

			Triangles.Add(BottomLeft);
			Triangles.Add(TopLeft);
			Triangles.Add(BottomRight);

			Triangles.Add(TopLeft);
			Triangles.Add(TopRight);
			Triangles.Add(BottomRight);
		}
	}
}