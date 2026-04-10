#pragma once

#include "CoreMinimal.h"
#include "Terrain/Terrain.h"
#include "SandFloor.generated.h"


UCLASS()
class MARINEENV_API ASandFloor : public ATerrain
{
	GENERATED_BODY()

public:
	ASandFloor();
    virtual void GenerateTerrain() override;
	int getXSize() const { return XSize; }
	void setXSize(int32 NewXSize) { XSize = NewXSize; }
	int getYSize() const { return YSize; }
	void setYSize(int32 NewYSize) { YSize = NewYSize; }
	float getScale() const { return Scale; }
	void setScale(float NewScale) { Scale = NewScale; }
	float getPerlinScale() const { return PerlinScale; }
	void setPerlinScale(float NewPerlinScale) { PerlinScale = NewPerlinScale; }
	int getSeed() const { return Seed; }
	void setSeed(int32 NewSeed) { Seed = NewSeed; }
	float getZMultiplier() const { return ZMultiplier; }
	void setZMultiplier(float NewZMultiplier) { ZMultiplier = NewZMultiplier; }
	float getUVScale() const { return UVScale; }
	void setUVScale(float NewUVScale) { UVScale = NewUVScale; }
	UMaterialInterface* getTerrainMaterial() const { return TerrainMaterial; }	
	void setTerrainMaterial(UMaterialInterface* NewTerrainMaterial) { TerrainMaterial = NewTerrainMaterial; }

protected:
	virtual void BeginPlay() override;

private:
    int XSize = 100;
    int YSize = 100;
    float Scale = 100.0f;
    float PerlinScale = 0.05f;
    float ZMultiplier = 500.0f;
    int Seed = 123;
    float UVScale = 0.1f;
    UMaterialInterface* TerrainMaterial;

	void CreateSandVertices();
	void CreateSandTriangles();
};