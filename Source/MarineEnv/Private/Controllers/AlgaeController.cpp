// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AlgaeController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

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
    float CollisionCheckRadius = 50.0f;
    float SpawnRadius = CollisionCheckRadius * 3.0f;

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
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);
            /*FActorSpawnParameters SpawnParam;
            SpawnParam.Owner = this;
            SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            */

            AAlgae* NewAlgae = GetWorld()->SpawnActorDeferred<AAlgae>(
                ParentAlgae->GetClass(),
                SpawnTransform,
                nullptr,
                nullptr,
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
            );

            if (NewAlgae)
            {
                NewAlgae->setEnergy(0.0f);
                NewAlgae->setState("Idle");

                UGameplayStatics::FinishSpawningActor(NewAlgae, SpawnTransform);
                NewAlgae->SpawnDefaultController();
                UE_LOG(LogTemp, Display, TEXT("New Algae successfully created at %s"), *SpawnLocation.ToString());
                return; // Successfully spawned
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Algae failed to find a clear spot to reproduce."));
}