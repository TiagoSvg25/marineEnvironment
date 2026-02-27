// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "NatureCharacteristics.h"
#include "GameFramework/Actor.h"
#include "Organism.generated.h"

UCLASS()
class MARINEENV_API AOrganism : public AActor
{
	GENERATED_BODY()
	
public:	
		// Sets default values for this actor's properties
	AOrganism();

	void updateMovement(float DeltaTime);

	void setPhysicalCharacteristics(float NewSize, float NewHeight, float NewWeight);

	void setEnvironmentalCharacteristics(EcoClass NewEcoclass, float NewMinDepth, float NewMaxDepth);

	void setMovementCharacteristics(float NewSpeed, float NewRadiusAwareness, float NewAngleVision);

	void setOrganismMeshe(UStaticMesh* mesh);


protected:
		// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FPhysicalCharacteristics Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FEnvironmentalCharacteristics Environmental;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FMovementCharacteristics Movement;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
