// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/SpawnOrganism.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
/*
ASpawnOrganism::ASpawnOrganism()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PrimaryActorTick.bCanEverTick = false;

}



// Called when the game starts or when spawned
void ASpawnOrganism::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpawnOrganism BeginPlay triggered"));
	Super::BeginPlay();

	FVector SpawnerLocation = this->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("OrgSpawner Position = %f, %f, %f"), SpawnerLocation.X, SpawnerLocation.Y, SpawnerLocation.Z);


	if (OrganismList.Num() == 0) {
		return;
	}
	while(this->spawnCount < entityLimit){
		for (UOrganismDataAsset* OrganismData : OrganismList) {
			if (OrganismData) {
				SpawnOrganism(OrganismData);
				this->spawnCount++;
			}
			if (this->spawnCount >= entityLimit) {
				break;
			}
		}
	}

}

void ASpawnOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnOrganism::SpawnOrganism(UOrganismDataAsset* OrganismData)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Trigger"));

	if (!OrganismData) return;


	//randomize spawn location

	FVector SpawnLocation;

	TArray<AActor*> Organisms;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOrganism::StaticClass(), Organisms);

	FRotator Rotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);


	int maxSpawnAttempt = 30;

	FVector Origin = this->GetActorLocation();

	bool invalidSpawn = true;

	for(int i = 0; i < maxSpawnAttempt; i++){

		invalidSpawn = false;

		double scaleNum = FMath::FRandRange(0.5,3);
		SpawnLocation.X = Origin.X + FMath::FRandRange(-width, width);
		SpawnLocation.Y = Origin.Y + FMath::FRandRange(-length, length);
		


		// check if other organisms are too close
		for (AActor* Actor : Organisms)
		{
			if (FVector::DistSquared(Actor->GetActorLocation(), SpawnLocation) > 0)
			{
				invalidSpawn = true;
				break;
			}
		}

		if (!invalidSpawn) {
			FTransform Transform(Rotation, SpawnLocation, FVector(scaleNum));

			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


			AOrganism* Organism = GetWorld()->SpawnActorDeferred<AOrganism>(
				AOrganism::StaticClass(),
				Transform,
				this,
				nullptr, 
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
			);

			if (Organism)
			{

				UGameplayStatics::FinishSpawningActor(Organism, Transform);

				Organism->SpawnDefaultController();
			}
			return;
		}
	}

}


void ASpawnOrganism::setSpawnRestrictions(double InWidth, double InLength, double InHeight, int InEntityLimit, TArray<UOrganismDataAsset*> InOrganismList) {
	this->width = InWidth;
	this->length = InLength;
	this->height = InHeight;
	this->entityLimit = InEntityLimit;
	this->OrganismList = InOrganismList;
}
*/
