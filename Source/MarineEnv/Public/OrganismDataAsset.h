// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AIController.h"
#include "OrganismDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API UOrganismDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, Category = "Scale")
    int Scale = 1;

    UPROPERTY(EditAnywhere, Category = "SpawnDensity")
    float SpawnDensity = 1.0f;

    UPROPERTY(EditAnywhere, Category = "DepthRange")
    float MinDepthRange = 0.f;

    UPROPERTY(EditAnywhere, Category = "DepthRange")
    float MaxDepthRange = 100.f;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimSequence* anim;

    UPROPERTY(EditAnywhere, Category = "Health")
    float Health = 1.0f;

    UPROPERTY(EditAnywhere, Category = "MaxHealth")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Tags")
    TArray<FString> Tags;

    UPROPERTY(EditAnywhere, Category = "Age")
    int Age = 0;


    UPROPERTY(EditDefaultsOnly, Category = "AI")
    TSubclassOf<AAIController> ControllerClass;

};
