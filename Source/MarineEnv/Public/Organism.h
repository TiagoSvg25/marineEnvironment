// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "NatureCharacteristics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Organism.generated.h"


UCLASS()
class MARINEENV_API AOrganism : public APawn
{
	GENERATED_BODY()
	
public:	
		// Sets default values for this actor's properties
	AOrganism();

	void updateMovement(float DeltaTime);

	void setPhysicalCharacteristics(float NewSize, float NewHeight, float NewWeight);

	void setEnvironmentalCharacteristics(EcoClass NewEcoclass, int NewTrophicLevel, float NewMinDepth, float NewMaxDepth);

	void setMovementCharacteristics(float NewSpeed, MovementState NewState, float NewRadiusAwareness, float NewTurnSpeed, float NewAngleVision);

	void setOrganismMeshe(USkeletalMesh* mesh, UAnimSequence* anim);

	void activateDetection(float DeltaTime);

protected:
		// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(VisibleAnywhere)
	UAnimSequence* anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FPhysicalCharacteristics Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FEnvironmentalCharacteristics Environmental;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	FMovementCharacteristics Movement;


	FVector CurrentDirection;

	FVector TargetDirection;

	float DirectionTimer;

	float DetectionTimer;

	FRotator NewRotation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DirectionChangeInterval;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DetectionInterval;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BehaviourAnalisys();	

	void UpdateBehaviour();

private:
	void calculateVectors();

};
