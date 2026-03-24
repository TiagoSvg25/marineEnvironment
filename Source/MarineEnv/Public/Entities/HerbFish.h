// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Animal.h"
#include "Plant.h"
#include "CoreMinimal.h"
#include "HerbFish.generated.h"

/**
 *
 */
UCLASS()

class MARINEENV_API AHerbFish : public AAnimal
{

	GENERATED_BODY()

public:


	AHerbFish();

	~AHerbFish();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FishMesh;


	UPROPERTY()
	UAnimSequence* Anim;


	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bIsPredator = false;

	virtual void setTargetHerb(APlant* newTarget);

	virtual APlant* getTargetHerb();

protected:

	APlant* TargetHerb;

};

