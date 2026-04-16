

#pragma once

#include "Entities/Animal.h"
#include "Controllers/ShoalManager.h"
#include "CoreMinimal.h"
#include "Fish.generated.h"

/**
 * 
 */
UCLASS()

class MARINEENV_API AFish : public AAnimal
{

	GENERATED_BODY()

public:


	AFish();  

	~AFish();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	FString getShoalId() const { return ShoalId; }

	TArray<AFish*> getNeighbors() const { return Neighbors; }

	void setShoalId(FString id) { ShoalId = id; }

	void setNeighbors(TArray<AFish*> neighbors) { Neighbors = neighbors; }

	UShoalManager* getShoalSubsystem() const { return ShoalSubsystem; }



	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FishMesh;


	UPROPERTY()
	UAnimSequence* Anim;


	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bIsPredator = false;

private:

	UShoalManager* ShoalSubsystem;

	FString ShoalId;

	TArray<AFish*> Neighbors;
};
