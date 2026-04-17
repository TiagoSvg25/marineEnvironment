#pragma once

#include "CoreMinimal.h"
#include "Controllers/Fish/FishController.h"
#include "Entities/Fish/Fish.h"
#include "Kismet/GameplayStatics.h"
#include "FlockingController.generated.h"

UCLASS()
class MARINEENV_API AFlockingController : public AFishController
{
    GENERATED_BODY()

public:
    AFlockingController();
    void BehaviourAnalisys(float DeltaTime) override;

private:
    void flockingBehaviour();
    void alignWithNeighbors();
    void cohesionWithNeighbors();
    void separateFromNeighbors();

    void alertShoalDanger();

    FVector AlignmentVector;
    FVector CohesionVector;
    FVector SeparationVector;

    float SeparationDistance = 200.0f;

    UPROPERTY(EditAnywhere, Category = "Flocking")
    float AlignWeight = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Flocking")
    float CohesionWeight = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Flocking")
    float SeparationWeight = 1.2f;
};