

#pragma once

#include "Animal.h"
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

	FVector CurrentDirection;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FishMesh;


};
