// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Plant/CoralController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ACoralController::ACoralController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}

void ACoralController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;


    //getModel()->setEnergy(getModel()->getEnergy() + (0.5f * DeltaTime));
    getModel()->setEnergy(getModel()->getEnergy() + 0.5f);

    FString CurrentState = getModel()->getCurrentState();

    if (CurrentState == "Idle") {
        if (getModel()->getEnergy() >= 100.0f) {
            getModel()->setEnergy(0.0f);
            getModel()->setState("Reproduce");
        }
    }
    else if (CurrentState == "Reproduce") {
        UE_LOG(LogTemp, Display, TEXT("The Coral entered reproduction!!!"));
        Reproduce();
        getModel()->setState("Idle");
    }
}

void ACoralController::Reproduce()
{
    ACoral* ParentCoral = getModel();
    if (!ParentCoral || !GetWorld()) return;

    USkeletalMeshComponent* MeshComp = ParentCoral->FindComponentByClass<USkeletalMeshComponent>();
    float MeshLength = 50.0f; // Default fallback

    if (MeshComp && MeshComp->GetSkeletalMeshAsset())
    {
        FBoxSphereBounds Bounds = MeshComp->GetSkeletalMeshAsset()->GetImportedBounds();
        MeshLength = Bounds.SphereRadius;
    }

    FVector ParentLocation = ParentCoral->GetActorLocation();

    float SpawnRadius = 500.f;
    float CollisionCheckRadius = MeshLength;

    for (int i = 0; i < 10; i++)
    {
        FVector RandomOffset = FMath::VRand() * SpawnRadius;
        FVector SpawnLocation = ParentLocation + (RandomOffset);
        SpawnLocation.Z = GetTerrainZ(SpawnLocation.X, SpawnLocation.Y);

        FCollisionShape Sphere = FCollisionShape::MakeSphere(CollisionCheckRadius);
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(ParentCoral);

        UE_LOG(LogTemp, Display, TEXT("Parent at: %s"), *ParentLocation.ToString());
        UE_LOG(LogTemp, Display, TEXT("Child at: %s"), *SpawnLocation.ToString());

        bool bIsOccupied = GetWorld()->OverlapAnyTestByChannel(
            SpawnLocation,
            FQuat::Identity,
            ECC_Pawn,
            Sphere,
            QueryParams
        );

        if (!bIsOccupied)
        {
            // Spawn the new Coral with SpawnActorDeferred
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

            ACoral* NewCoral = GetWorld()->SpawnActorDeferred<ACoral>(
                ParentCoral->GetClass(),
                SpawnTransform,
                nullptr,
                nullptr,
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
            );

            if (NewCoral)
            {
                NewCoral->setEnergy(0.1f);
                NewCoral->setState("Idle");

                UGameplayStatics::FinishSpawningActor(NewCoral, SpawnTransform);
                //NewAlgae->SpawnDefaultController();
                UE_LOG(LogTemp, Display, TEXT("New Coral successfully created at %s"), *SpawnLocation.ToString());
                return; // Successfully spawned
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Coral failed to find a clear spot to reproduce."));
}