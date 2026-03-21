// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AlgaeController.h"
#include "Engine/World.h"

AAlgaeController::AAlgaeController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}

void AAlgaeController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;


    //getModel()->setEnergy(getModel()->getEnergy() + (0.5f * DeltaTime));
    getModel()->setEnergy(getModel()->getEnergy() + 0.1f);

    FString CurrentState = getModel()->getCurrentState();

    if (CurrentState == "Idle") {
        if (getModel()->getEnergy() >= 100.0f) {
            getModel()->setState("Reproduce");
        }
    }
    else if (CurrentState == "Reproduce") {
        UE_LOG(LogTemp, Display, TEXT("The algae entered reproduction!!!"));
        Reproduce();
        getModel()->setState("Idle");
    }
}

void AAlgaeController::Reproduce()
{
    AAlgae* ParentAlgae = getModel();
    if (!ParentAlgae || !GetWorld()) return;

    FVector ParentLocation = ParentAlgae->GetActorLocation();
    float SpawnRadius = 200.0f; // Distance from parent
    float CollisionCheckRadius = 50.0f;

    for (int i = 0; i < 10; i++)
    {
        FVector RandomOffset = FVector(FMath::FRandRange(-1.0f, 1), FMath::FRandRange(-1.0f, 1), 0.0f);
        RandomOffset.Normalize();
        FVector SpawnLocation = ParentLocation + (RandomOffset * SpawnRadius);

        // Check for collisions with other Organisms (Pawns/Actors)
        FCollisionShape Sphere = FCollisionShape::MakeSphere(CollisionCheckRadius);
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(ParentAlgae);

        // Check if the area is clear
        bool bIsOccupied = GetWorld()->OverlapAnyTestByChannel(
            SpawnLocation,
            FQuat::Identity,
            ECC_Pawn, // Assuming Organisms use the Pawn channel
            Sphere,
            QueryParams
        );

        if (!bIsOccupied)
        {
            // Spawn the new Algae
            /*FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            AAlgae* NewAlgae = GetWorld()->SpawnActor<AAlgae>(ParentAlgae->GetClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams); // BIG BUG

            if (NewAlgae)
            {
                NewAlgae->setEnergy(0.0f);
                NewAlgae->setState("Idle");
                UE_LOG(LogTemp, Display, TEXT("New Algae successfully created at %s"), *SpawnLocation.ToString());
                return; // Successfully spawned
            }*/
            UE_LOG(LogTemp, Display, TEXT("New Algae successfully created at %s"), *SpawnLocation.ToString());
            getModel()->setEnergy(0.1f);
            return;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Algae failed to find a clear spot to reproduce."));
}