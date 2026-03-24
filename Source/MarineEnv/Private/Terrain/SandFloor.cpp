#include "Terrain/SandFloor.h"


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
	GenerateTerrain();
}

void ASandFloor::GenerateTerrain()
{
	if (!ProceduralMesh) return;

	Vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	ProceduralMesh->ClearMeshSection(0);

	CreateSandVertices();
	CreateSandTriangles();

	ProceduralMesh->CreateMeshSection(
		0,
		Vertices,
		Triangles,
		TArray<FVector>(),
		UV0,
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		true
	);

	if (getTerrainMaterial())
	{
		ProceduralMesh->SetMaterial(0, getTerrainMaterial());
	}
}

void ASandFloor::CreateSandVertices()
{
	for (int32 X = 0; X <= getXSize(); ++X)
	{
		for (int32 Y = 0; Y <= getYSize(); ++Y)
		{
			FVector2D NoiseInput = FVector2D(X + 0.1f + getSeed(), Y + 0.1f + getSeed()) * getPerlinScale();

			float NoiseValue = FMath::PerlinNoise2D(NoiseInput);
			float Z = (NoiseValue + 1.0f) * getZMultiplier();

			Vertices.Add(FVector(X * getScale(), Y * getScale(), Z));
			UV0.Add(FVector2D(X * getUVScale(), Y * getUVScale()));
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