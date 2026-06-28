#include "Terrain/SandFloor.h"
#include <MarineEnv/MarineEnvGameModeBase.h>
#include "MarineGameInstance.h"
#include "KismetProceduralMeshLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


ASandFloor::ASandFloor()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFinder(
		TEXT("/Game/MyTexture.MyTexture")
	);

	this->Tags.Add(FName("SandFloor"));

	if (MatFinder.Succeeded())
	{
		TerrainMaterial = MatFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FoundBubbleAsset(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/Bubbles.Bubbles'")
	);

	if (FoundBubbleAsset.Succeeded())
	{
		BubbleAsset = FoundBubbleAsset.Object;
	}
}
void ASandFloor::BeginPlay()
{
	Super::BeginPlay();
	UMarineGameInstance* GI = Cast<UMarineGameInstance>(GetGameInstance());

	if (!GI) return;

	float ScaleFactor = GI->MapSize / getXSize();
	setScale(ScaleFactor);
	setZMultiplier(5 * ScaleFactor);

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

	SpawnDistributedBubbles();
}

void ASandFloor::SpawnDistributedBubbles()
{
	if (!BubbleAsset || !ProceduralMesh) return;

	// Clear out any old components if terrain is regenerated
	for (UNiagaraComponent* Comp : BubbleComponents)
	{
		if (Comp) Comp->DestroyComponent();
	}
	BubbleComponents.Empty();

	const int32 DistributionStep = 10;

	int32 VertsXCount = getXSize() + 1;
	int32 VertsYCount = getYSize() + 1;

	for (int32 XIdx = 0; XIdx < VertsXCount; XIdx += DistributionStep)
	{
		for (int32 YIdx = 0; YIdx < VertsYCount; YIdx += DistributionStep)
		{
			int32 FlatVertexIndex = (XIdx * VertsYCount) + YIdx;

			if (Vertices.IsValidIndex(FlatVertexIndex))
			{
				FVector LocalSpawnLocation = Vertices[FlatVertexIndex];

				FString DynamicCompName = FString::Printf(TEXT("SandBubbleGen_%d_%d"), XIdx, YIdx);

				UNiagaraComponent* NewBubbleComp = NewObject<UNiagaraComponent>(this, FName(*DynamicCompName));
				if (NewBubbleComp)
				{
					NewBubbleComp->RegisterComponent();
					NewBubbleComp->SetAsset(BubbleAsset);

					NewBubbleComp->AttachToComponent(ProceduralMesh, FAttachmentTransformRules::KeepRelativeTransform);
					NewBubbleComp->SetRelativeLocation(LocalSpawnLocation);

					NewBubbleComp->Activate();

					BubbleComponents.Add(NewBubbleComp);
				}
			}
		}
	}
}

void ASandFloor::CreateSandVertices()
{
	float MaxDepth = 0.0f;
	float MinDepth = getZMultiplier();

	for (int32 X = -getXSize()/2; X <= getXSize()/2; ++X)
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