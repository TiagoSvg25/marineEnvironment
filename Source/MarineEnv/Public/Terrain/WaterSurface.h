// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Terrain/Terrain.h"
#include "WaterSurface.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AWaterSurface : public ATerrain
{
	GENERATED_BODY()

public:
	AWaterSurface();
	virtual void GenerateTerrain() override;
	int getXSize() const { return XSize; }
	void setXSize(int32 NewXSize) { XSize = NewXSize; }
	int getYSize() const { return YSize; }
	void setYSize(int32 NewYSize) { YSize = NewYSize; }
	float getScale() const { return Scale; }
	void setScale(float NewScale) { Scale = NewScale; }
	float getUVScale() const { return UVScale; }
	void setUVScale(float NewUVScale) { UVScale = NewUVScale; }
	int getWaterHeight() const { return waterHeight; }
	void setWaterHeight(int NewWaterHeight) { waterHeight = NewWaterHeight; }
	UMaterialInterface* getWaterMaterial() const { return WaterMaterial; }
	void setTerrainMaterial(UMaterialInterface* NewWaterMaterial) { WaterMaterial = NewWaterMaterial; }

protected:
	virtual void BeginPlay() override;

private:
	int XSize = 100;
	int YSize = 100;
	float Scale = 100.0f;
	float UVScale = 0.1f;
	UMaterialInterface* WaterMaterial;
	float waterHeight = 8000.0f;


	void CreateWaterVertices();
	void CreateWaterTriangles();
};

