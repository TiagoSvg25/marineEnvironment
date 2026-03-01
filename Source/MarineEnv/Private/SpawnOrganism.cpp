// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnOrganism.h"
#include "Kismet/GameplayStatics.h"

// Sets default values

ASpawnOrganism::ASpawnOrganism()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



// Called when the game starts or when spawned
void ASpawnOrganism::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpawnOrganism BeginPlay triggered"));
	Super::BeginPlay();
	int spawnCount = 0;
	UE_LOG(LogTemp, Warning, TEXT("OrganismList Size = %d"), OrganismList.Num());
	UE_LOG(LogTemp, Warning, TEXT("Entity Limit = %d"), entityLimit);

	if (OrganismList.Num() == 0) {
		return;
	}

	while(spawnCount < entityLimit){
		for (UOrganismDataAsset* OrganismData : OrganismList) {
			if (OrganismData) {
				SpawnOrganism(OrganismData);
				spawnCount++;
			}
			if (spawnCount >= entityLimit) {
				break;
			}
		}
	}
}

void ASpawnOrganism::SpawnOrganism(UOrganismDataAsset* OrganismData)
{

	if (!OrganismData) return;


	//randomize spawn location

	FVector SpawnLocation;

	TArray<AActor*> Organisms;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOrganism::StaticClass(), Organisms);

	FRotator Rotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);


	int maxSpawnAttempt = 30;

	FVector Origin = GetActorLocation();

	bool invalidSpawn = false;

	float MinDistSq = FMath::Square(OrganismData->Physical.Size*1.5);

	for(int i = 0; i < maxSpawnAttempt; i++){

		invalidSpawn = false;

		SpawnLocation.X = Origin.X + FMath::FRandRange(-width, width);
		SpawnLocation.Y = Origin.Y + FMath::FRandRange(-length, length);
		SpawnLocation.Z = Origin.Z + FMath::FRandRange(height - OrganismData->Environmental.MaxDepth + OrganismData->Physical.Height,height - OrganismData->Environmental.MinDepth);

		// check if other organisms are too close
		for (AActor* Actor : Organisms)
		{
			if (FVector::DistSquared(Actor->GetActorLocation(), SpawnLocation) < MinDistSq)
			{
				invalidSpawn = true;
				break;
			}
		}

		if (!invalidSpawn) {
			FTransform Transform(Rotation, SpawnLocation);

			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


			AOrganism* Organism = GetWorld()->SpawnActorDeferred<AOrganism>(AOrganism::StaticClass(),Transform,this,nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

			if (Organism)
			{
				fill_information(OrganismData, Organism);

				UGameplayStatics::FinishSpawningActor(Organism, Transform);
			}
			return;
		}
	}

}

void ASpawnOrganism::fill_information(UOrganismDataAsset* OrganismDat, AOrganism* Organism)
{
	Organism->setEnvironmentalCharacteristics(OrganismDat->Environmental.EcoType, OrganismDat->Environmental.MinDepth, OrganismDat->Environmental.MaxDepth);
	Organism->setPhysicalCharacteristics(OrganismDat->Physical.Size, OrganismDat->Physical.Height, OrganismDat->Physical.Weight);
	Organism->setMovementCharacteristics(OrganismDat->Movement.Speed, OrganismDat->Movement.AwarenessRadius, OrganismDat->Movement.AngleVision);
	Organism->setOrganismMeshe(OrganismDat->Mesh);
}

void ASpawnOrganism::setSpawnRestrictions(double InWidth, double InLength, double InHeight, int InEntityLimit, TArray<UOrganismDataAsset*> InOrganismList) {
	this->width = InWidth;
	this->length = InLength;
	this->height = InHeight;
	this->entityLimit = InEntityLimit;
	this->OrganismList = InOrganismList;

}
