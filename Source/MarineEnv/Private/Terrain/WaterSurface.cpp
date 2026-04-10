// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain/WaterSurface.h"


AWaterSurface::AWaterSurface()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> WaterMesh(TEXT("/Script/Engine.Material'/Game/Material/M_Water.M_Water'"));

	if (WaterMesh.Succeeded())
	{
		WaterMaterial = WaterMesh.Object;
	}


	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWaterSurface::BeginPlay()
{
	Super::BeginPlay();
	GenerateTerrain();
}

void AWaterSurface::GenerateTerrain()
{
	if (!ProceduralMesh) return;

	Vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	ProceduralMesh->ClearMeshSection(0);


	CreateWaterVertices();
	CreateWaterTriangles();

	ProceduralMesh->CreateMeshSection(
		0,
		Vertices,
		Triangles,
		TArray<FVector>(),
		UV0,
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		false
	);

	if (getWaterMaterial())
	{
		ProceduralMesh->SetMaterial(0, getWaterMaterial());
	}
}

void AWaterSurface::CreateWaterVertices()
{
	for (int32 X = 0; X <= getXSize(); ++X)
	{
		for (int32 Y = 0; Y <= getYSize(); ++Y)
		{
			Vertices.Add(FVector(X * getScale(), Y * getScale(), getWaterHeight()));
			UV0.Add(FVector2D(X * getUVScale(), Y * getUVScale()));
		}
	}
}

void AWaterSurface::CreateWaterTriangles()
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
