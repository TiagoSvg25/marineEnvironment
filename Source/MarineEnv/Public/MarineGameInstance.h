// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Entities/Organism.h"
#include "MarineGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API UMarineGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Simulation Config")
	TMap<TSubclassOf<AOrganism>, int32> SelectedOrganisms;

    UPROPERTY(BlueprintReadWrite, Category = "Settings")
    float MapSize = 10000.f;

    UFUNCTION(BlueprintCallable, Category = "Settings")
    void SetOrganismCount(TSubclassOf<AOrganism> OrganismClass, int32 Count)
    {
        SelectedOrganisms.Add(OrganismClass, Count);
    }

    UFUNCTION(BlueprintCallable, Category = "Settings")
    int32 GetOrganismCount(TSubclassOf<AOrganism> OrganismClass)
    {
        int32* Found = SelectedOrganisms.Find(OrganismClass);
        return Found ? *Found : 0;
    }

};
