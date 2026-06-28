// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Organism.generated.h"


class AOrganismAIController;

UCLASS()
class MARINEENV_API AOrganism : public APawn
{
	GENERATED_BODY()
	
public:	
		// Sets default values for this actor's properties
	AOrganism();


	float getMinDepthRange() const;

	float getMaxDepthRange() const;

	void setMinDepthRange(float NewMinDepthRange);

	void setMaxDepthRange(float NewMaxDepthRange);

	USkeletalMeshComponent* getMeshAsset() const;

	void setMeshAsset(USkeletalMeshComponent* NewMeshAsset);

	UAnimSequence* getAnimAsset() const;

	void setAnimAsset(UAnimSequence* NewAnimAsset);

	TArray<FString> getTags() const;

	void setTags(const TArray<FString>& NewTags);

	void addTag(const FString& NewTag);

	float getEnergy() const;

	void setEnergy(float NewEnergy);

	float getEnergyConsumptionRate() const;

	void setEnergyConsumptionRate(float NewEnergyConsumptionRate);

	float getEnergyThreshold() const;

	void setEnergyThreshold(float NewHungerThreshold);

	float getMaxEnergy() const;

	void setMaxEnergy(float NewMaxEnergy);

	FString getCurrentState() const;

	void setState(const FString& NewState);

	UFUNCTION()
	void OnOrganismOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHitTerrain(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

protected:

	float MinDepthRange = 0.f;
	float MaxDepthRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organism")
	float Energy = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organism")
	float EnergyThreshold = 50.0f;
	float MaxEnergy = 100.0f;
	float EnergyConsumptionRate = 0.2f;

	USkeletalMeshComponent* MeshAsset;
	UAnimSequence* anim;
	TArray<FString> Tags = { "dummy" };
	FString CurrentState = "Idle";
	int Age = 0;
	TSubclassOf<AAIController> ControllerClass;
	UBoxComponent* CollisionBox;


	// Called when the game starts or when spawned

	/*UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(VisibleAnywhere)
	UAnimSequence* anim


	*/
};
