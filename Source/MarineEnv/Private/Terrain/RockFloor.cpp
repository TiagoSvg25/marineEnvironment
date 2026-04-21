// Fill out your copyright notice in the Description page of Project Settings.

#include "Terrain/RockFloor.h"
#include "Math/UnrealMathUtility.h"

ARockFloor::ARockFloor() {}

void ARockFloor::BeginPlay()
{
    Super::BeginPlay();
    GenerateTerrain();

}

void ARockFloor::GenerateTerrain()
{
    if (!ProceduralMesh) return;

    Vertices.Empty();
    Triangles.Empty();
    UV0.Empty();
    ProceduralMesh->ClearMeshSection(0);

    CreateVertices();
    CreateTriangles();

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
}

void ARockFloor::CreateVertices()
{
	for (int32 X = -XSize/2; X <= XSize/2; ++X)
	{
		for (int32 Y = -YSize/2; Y <= YSize/2; ++Y)
		{
            // Simple random bumps instead of Perlin — no plugin needed
            float Z = FMath::RandRange(-1.0f, 1.0f) * ZMultiplier;

            Vertices.Add(FVector(X * Scale, Y * Scale, Z));
            UV0.Add(FVector2D(X * UVScale, Y * UVScale));
        }
    }
}

void ARockFloor::CreateTriangles()
{
    for (int32 X = 0; X < XSize; ++X)
    {
        for (int32 Y = 0; Y < YSize; ++Y)
        {
            int32 BottomLeft = (X * (YSize + 1)) + Y;
            int32 BottomRight = ((X + 1) * (YSize + 1)) + Y;
            int32 TopLeft = (X * (YSize + 1)) + (Y + 1);
            int32 TopRight = ((X + 1) * (YSize + 1)) + (Y + 1);

            Triangles.Add(BottomLeft);
            Triangles.Add(TopLeft);
            Triangles.Add(BottomRight);

            Triangles.Add(TopLeft);
            Triangles.Add(TopRight);
            Triangles.Add(BottomRight);
        }
    }
}