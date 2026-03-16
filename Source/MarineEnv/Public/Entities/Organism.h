// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "DataAssets/OrganismDataAsset.h"
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

	virtual UOrganismDataAsset* getDataAsset() const
	{
		return DataAsset; // será o UAnimalDataAsset criado pelo AAnimal
	}

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
	UPROPERTY()
	UOrganismDataAsset* DataAsset;

	// Called when the game starts or when spawned

	/*UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(VisibleAnywhere)
	UAnimSequence* anim


	*/
};
