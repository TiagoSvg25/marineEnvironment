// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Organism.generated.h"


class AOrganismAIController;

UCLASS()
class MARINEENV_API AOrganism : public APawn
{
	GENERATED_BODY()
	
public:	
		// Sets default values for this actor's properties
	AOrganism();

	float getHealth() const;

	void setHealth(float NewHealth);

	int getAge() const;

	void setAge(int NewAge);

	int getScale() const;

	void setScale(int NewScale);

	float getSpawnDensity() const;

	void setSpawnDensity(float NewSpawnDensity);

	float getMinDepthRange() const;

	float getMaxDepthRange() const;

	void setMinDepthRange(float NewMinDepthRange);

	void setMaxDepthRange(float NewMaxDepthRange);

	USkeletalMesh* getMeshAsset() const;

	void setMeshAsset(USkeletalMesh* NewMeshAsset);

	UAnimSequence* getAnimAsset() const;

	void setAnimAsset(UAnimSequence* NewAnimAsset);

	TArray<FString> getTags() const;

	void setTags(const TArray<FString>& NewTags);


	/**UFUNCTION()
	void OnOrganismOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHitTerrain(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);*/

protected:


	int Scale = 1;
	float SpawnDensity = 1.0f;
	float MinDepthRange = 0.f;
	float MaxDepthRange = 100.f;
	USkeletalMesh* MeshAsset;
	UAnimSequence* anim;
	float Health = 1.0f;
	float MaxHealth = 100.0f;
	TArray<FString> Tags = { "dummy" };
	int Age = 0;
	TSubclassOf<AAIController> ControllerClass;
	USphereComponent* CollisionSphere;

	// Called when the game starts or when spawned

	/*UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(VisibleAnywhere)
	UAnimSequence* anim


	*/
};
