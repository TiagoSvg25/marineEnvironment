#include "Entities/Animal.h"
#include "Controllers/AnimalAIController.h"



AAnimal::AAnimal()
{
	AnimalDataAsset = CreateDefaultSubobject<UAnimalDataAsset>(TEXT("AnimalDataAsset"));

	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAnimalAIController::StaticClass();

}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = AnimalDataAsset->InitialState;
}

void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



