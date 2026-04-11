// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fish.h"
#include "Controllers/Fish/SharkController.h"
#include "Shark.generated.h"

/**
 * 
 */
UCLASS()
class MARINEENV_API AShark : public AFish
{
	GENERATED_BODY()
	
public:

	AShark();

	void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* AnimSwim;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FishMesh;


	UPROPERTY()
	UAnimSequence* Anim;

};
