// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/BaseSpawner.h"
#include "Spawner/SpawnOrganism.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABaseSpawner::ABaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnerLocation = this->GetActorLocation(); 
	FTransform SpawnTransform(FRotator::ZeroRotator, SpawnerLocation, FVector::OneVector);
	UE_LOG(LogTemp, Warning, TEXT("BaseSpawner Position = %f, %f, %f"), SpawnerLocation.X, SpawnerLocation.Y, SpawnerLocation.Z);

	ASpawnOrganism* OrgSpawner = GetWorld()->SpawnActorDeferred<ASpawnOrganism>(ASpawnOrganism::StaticClass(), SpawnTransform);

	if (OrgSpawner) {
		OrgSpawner->setSpawnRestrictions(
			width,
			length,
			height,
			entityLimit,
			OrganismList
		);

		UGameplayStatics::FinishSpawningActor(OrgSpawner, SpawnTransform);


		FVector ORG = OrgSpawner->GetActorLocation();

		UE_LOG(LogTemp, Warning, TEXT("BaseSpawner Position = %f, %f, %f"), ORG.X, ORG.Y, ORG.Z);
	}

}

// Called every frame
void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

