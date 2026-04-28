#include "Spawner/PropGenerator.h" 
#include <MarineEnv/MarineEnvGameModeBase.h>
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

APropGenerator::APropGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BubbleAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/Bubbles.Bubbles'"));
	if (BubbleAsset.Succeeded())
	{
		BubbleSystem = BubbleAsset.Object;
	}
}

void APropGenerator::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < PropMeshes.Num(); i++)
	{
		if (PropMeshes[i] != nullptr)
		{
			UHierarchicalInstancedStaticMeshComponent* NewHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
			
			NewHISM->SetStaticMesh(PropMeshes[i]);

			if (bEnableCollision)
			{
				NewHISM->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				NewHISM->SetCollisionResponseToAllChannels(ECR_Block);
			}
			else
			{
				NewHISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}

			NewHISM->SetupAttachment(RootComponent);
			NewHISM->RegisterComponent();

			HISMComponents.Add(NewHISM);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APropGenerator::GenerateProps, 1.5f, false);
}

void APropGenerator::GenerateProps()
{
	if (HISMComponents.Num() == 0) return;

	AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

	
	TArray<TArray<FTransform>> TransformsPerMesh;
	TransformsPerMesh.SetNum(HISMComponents.Num());

	FVector Origin = GetActorLocation();

	for (int i = 0; i < NumberOfInstances; i++)
	{
		float RandX = Origin.X + FMath::RandRange(-GameMode->WorldLength / 2, GameMode->WorldLength / 2 );
		float RandY = Origin.Y + FMath::RandRange(-GameMode->WorldWidth / 2, GameMode->WorldWidth / 2);

		float TerrainZ = GetTerrainZ(RandX, RandY);
		float RandomScale = FMath::RandRange(MinScale, MaxScale);

		
		float FinalZ = TerrainZ - (SinkDepth * RandomScale);

		FVector SpawnLocation = FVector(RandX, RandY, FinalZ);
		FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
		FVector SpawnScale = FVector(RandomScale);

		FTransform NewTransform(SpawnRotation, SpawnLocation, SpawnScale);

		int RandomMeshIndex = FMath::RandRange(0, HISMComponents.Num() - 1);

		TransformsPerMesh[RandomMeshIndex].Add(NewTransform);
	}

	
	for (int32 i = 0; i < HISMComponents.Num(); i++)
	{
		if (TransformsPerMesh[i].Num() > 0)
		{
			HISMComponents[i]->AddInstances(TransformsPerMesh[i], false);

			
			HISMComponents[i]->BuildTreeIfOutdated(true, false);
		}
	}

	if (BubbleSystem) {
		for (int i = 0; i < NumberOfBubblePoints; i++)
		{
			float RandX = Origin.X + FMath::RandRange(-GameMode->WorldLength / 2, GameMode->WorldLength / 2);
			float RandY = Origin.Y + FMath::RandRange(-GameMode->WorldWidth / 2, GameMode->WorldWidth / 2);

			float TerrainZ = GetTerrainZ(RandX, RandY);
			
			FVector BubbleLocation = FVector(RandX, RandY, TerrainZ);

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				BubbleSystem,
				BubbleLocation,
				FRotator::ZeroRotator,
				FVector(1.0f),
				true
			);
		}
	}
}

/*float APropGenerator::GetTerrainZ(float LocationX, float LocationY)
{
	FVector TraceStart = FVector(LocationX, LocationY, 10000.f);
	FVector TraceEnd = FVector(LocationX, LocationY, -10000.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
	{
		return Hit.ImpactPoint.Z;
	}

	return 0.f;
}*/

float APropGenerator::GetTerrainZ(float LocationX, float LocationY)
{
	FVector TraceStart = FVector(LocationX, LocationY, 10000.f);
	FVector TraceEnd = FVector(LocationX, LocationY, -10000.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
	{
		if (Hit.GetActor() && Hit.GetActor()->ActorHasTag(FName("SandFloor")))
		{
			return Hit.ImpactPoint.Z;
		}
	}
	return 0.f;
}