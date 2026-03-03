// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NatureCharacteristics.h"
#include "OrganismDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API UOrganismDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, Category = "Physical")
    FPhysicalCharacteristics Physical;

    UPROPERTY(EditAnywhere, Category = "Environmental")
    FEnvironmentalCharacteristics Environmental;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FMovementCharacteristics Movement;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    USkeletalMesh* Mesh;

    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimSequence* anim;

};
