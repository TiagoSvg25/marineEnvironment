// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner/OrganismSpawner.h"
#include "Engine/World.h"
#include "WorldCollision.h"


// Sets default values
AOrganismSpawner::AOrganismSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrganismSpawner::BeginPlay()
{
	Super::BeginPlay();

    for (auto& Entry : spawnCounts)
    {
        TSubclassOf<AOrganism> OrganismClass = Entry.Key;
        int32 Count = Entry.Value;

        AOrganism* DefaultOrganism = OrganismClass->GetDefaultObject<AOrganism>();

        for (int32 i = 0; i < Count; i++)
        {
            Spawn(OrganismClass, GetWorld());
        }
    }
}

void AOrganismSpawner::Spawn(UClass* OrganismClass, UWorld* World)
{
	if (!OrganismClass || !World) return;

    AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

    if (!GameMode) return;

    int maxSpawnAttempt = 30;

    bool invalidSpawn = true;

    for (int i = 0; i < maxSpawnAttempt; i++) {
        float LocationX =FMath::RandRange(0.f, GameMode->WorldLength);

        float LocationY = FMath::RandRange(0.f, GameMode->WorldWidth);

        FVector Location = FVector(
            LocationX,
            LocationY,
            FMath::RandRange(GetTerrainZ(LocationX, LocationY), GameMode->WorldHeight)
        );

        TArray<AActor*> OverlappingActors;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
        TArray<AActor*> ToIgnore;
        ToIgnore.Add(this);

        bool bOccupied = UKismetSystemLibrary::SphereOverlapActors(
            World,
            Location,
            10.f,
            ObjectTypes,
            AOrganism::StaticClass(),
            ToIgnore,
            OverlappingActors
        ) && OverlappingActors.Num() > 0;

        if (!bOccupied)
        {
            AOrganism* NewOrganism = World->SpawnActor<AOrganism>(OrganismClass, Location, FRotator::ZeroRotator);
            if (NewOrganism)
            {
                UE_LOG(LogTemp, Display, TEXT("Spawned %s at %s"), *OrganismClass->GetName(), *Location.ToString());
                return;
            }
            break;
        }
    }
}

float AOrganismSpawner::GetTerrainZ(float LocationX, float LocationY) {
    FVector TraceStart = FVector(LocationX, LocationY, 10000.f); 
    FVector TraceEnd = FVector(LocationX, LocationY, -10000.f);  

    FHitResult Hit;
    FCollisionQueryParams Params;

    if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
    {
        return Hit.ImpactPoint.Z; 
    }

    return 0.f; 
}


