// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawner.h"
#include "SpawnOrganism.h"
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
	FTransform SpawnTransform(GetActorLocation());

	ASpawnOrganism* OrgSpawner = GetWorld()->SpawnActorDeferred<ASpawnOrganism>(ASpawnOrganism::StaticClass(), SpawnTransform);

	if (OrgSpawner) {
		OrgSpawner->setSpawnRestrictions(
			width,
			length,
			height,
			entityLimit,
			OrganismList
		);
	}
	UGameplayStatics::FinishSpawningActor(OrgSpawner, SpawnTransform);


}

// Called every frame
void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

