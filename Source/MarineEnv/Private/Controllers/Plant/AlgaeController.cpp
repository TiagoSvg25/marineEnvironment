// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Plant/AlgaeController.h"
#include "Engine/World.h"
#include "WorldCollision.h"
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
            getModel()->setEnergy(0.0f);
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

    USkeletalMeshComponent* MeshComp = ParentAlgae->FindComponentByClass<USkeletalMeshComponent>();
    float MeshLength = 100.0f; // Default fallback

    if (MeshComp && MeshComp->GetSkeletalMeshAsset())
    {
        FBoxSphereBounds Bounds = MeshComp->GetSkeletalMeshAsset()->GetImportedBounds();
        MeshLength = Bounds.SphereRadius;
    }

    FVector ParentLocation = ParentAlgae->GetActorLocation();

    float SpawnRadius = 500.f;
    float CollisionCheckRadius = 100.f;

    for (int i = 0; i < 10; i++)
    {
        FVector RandomOffset = FVector(FMath::RandRange(200.0f,700.f), FMath::RandRange(200.0f, 700.f), 0);
        FVector SpawnLocation = ParentLocation + (RandomOffset);
        SpawnLocation.Z = GetTerrainZ(SpawnLocation.X, SpawnLocation.Y);


        TArray<AActor*> OverlappingActors;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
        TArray<AActor*> ToIgnore;
        ToIgnore.Add(getModel());

        UE_LOG(LogTemp, Display, TEXT("Parent at: %s"), *ParentLocation.ToString());
        UE_LOG(LogTemp, Display, TEXT("Child at: %s"), *SpawnLocation.ToString());

        bool bIsOccupied = UKismetSystemLibrary::SphereOverlapActors(
            GetWorld(),
            SpawnLocation,
            50.f,
            ObjectTypes,
            AOrganism::StaticClass(),
            ToIgnore,
            OverlappingActors
        ) && OverlappingActors.Num() > 0;

        if (!bIsOccupied)
        {
            // Spawn the new Algae with SpawnActorDeferred
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

            AAlgae* NewAlgae = GetWorld()->SpawnActorDeferred<AAlgae>(
                ParentAlgae->GetClass(),
                SpawnTransform,
                nullptr,
                nullptr,
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
            );

            if (NewAlgae)
            {
                NewAlgae->setEnergy(0.1f);
                NewAlgae->setState("Idle");
                SnapToFloor(SpawnLocation);
                NewAlgae->SetActorLocation(SpawnLocation);

                UGameplayStatics::FinishSpawningActor(NewAlgae, SpawnTransform);
                //NewAlgae->SpawnDefaultController();
                UE_LOG(LogTemp, Display, TEXT("New Algae successfully created at %s"), *SpawnLocation.ToString());
                return; // Successfully spawned
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Algae failed to find a clear spot to reproduce."));
}