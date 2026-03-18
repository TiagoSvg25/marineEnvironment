#include "Entities/Animal.h"
#include "Controllers/AnimalAIController.h"



AAnimal::AAnimal()
{

	DataAsset = CreateDefaultSubobject<UAnimalDataAsset>(TEXT("AnimalDataAsset"));

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	RootComponent = CollisionComponent;

	CollisionComponent->InitSphereRadius(50.0f);

	CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));

	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAnimalAIController::StaticClass();
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	if (UAnimalDataAsset* Asset = getDataAsset())
	{
		CurrentState = "Idle";
		CurrentEnergy = Asset->MaxEnergy; 
		CurrentSpeed = Asset->BaseSpeed;
		CurrentTargetLocation = GetActorLocation(); 
	}
}

void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




FString AAnimal::getCurrentState() const
{
	return CurrentState;
}

void AAnimal::setState(const FString& NewState)
{
	CurrentState = NewState;
}

float AAnimal::getBaseSpeed() const
{
	return getDataAsset()->BaseSpeed;
}

float AAnimal::getAwarenessRadius() const
{
	return getDataAsset()->AwarenessRadius;
}

void AAnimal::setAwarenessRadius(float NewAwarenessRadius)
{
	getDataAsset()->AwarenessRadius = NewAwarenessRadius;
}

float AAnimal::getAngleVision() const
{
	return getDataAsset()->AngleVision;
}

void AAnimal::setAngleVision(float NewAngleVision)
{
	getDataAsset()->AngleVision = NewAngleVision;
}

int AAnimal::getTrophicLevel() const
{
	return getDataAsset()->TrophicLevel;
}

void AAnimal::setTrophicLevel(int NewTrophicLevel)
{
	getDataAsset()->TrophicLevel = NewTrophicLevel;
}

float AAnimal::getDirectionChangeInterval() const
{
	return getDataAsset()->DirectionChangeInterval;
}

void AAnimal::setDirectionChangeInterval(float NewDirectionChangeInterval)
{
	getDataAsset()->DirectionChangeInterval = NewDirectionChangeInterval;
}



float AAnimal::getSpeed() const
{
	return CurrentSpeed;
}

void AAnimal::setSpeed(float NewSpeed)
{
	CurrentSpeed = NewSpeed;
}

float AAnimal::getEnergyThreshold() const
{
	return getDataAsset()->EnergyThreshold;
}

void AAnimal::setEnergyThreshold(float NewEnergyThreshold)
{
	getDataAsset()->EnergyThreshold = NewEnergyThreshold;
}

float AAnimal::getMaxEnergy() const
{
	return getDataAsset()->MaxEnergy;
}

void AAnimal::setMaxEnergy(float NewMaxEnergy)
{
	getDataAsset()->MaxEnergy = NewMaxEnergy;
}



float AAnimal::getEnergy() const {
	return CurrentEnergy;
}

void AAnimal::setEnergy(float NewEnergy) {
	CurrentEnergy = NewEnergy;
}

float AAnimal::getEnergyConsumptionRate() const
{
	return getDataAsset()->EnergyConsumptionRate;
}

void AAnimal::setEnergyConsumptionRate(float NewEnergyConsumptionRate)
{
	getDataAsset()->EnergyConsumptionRate = NewEnergyConsumptionRate;
}

float AAnimal::getTurnSpeed() const
{
	return getDataAsset()->TurnSpeed;
}


void AAnimal::setTurnSpeed(float NewTurnSpeed)
{
	getDataAsset()->TurnSpeed = NewTurnSpeed;
}

void AAnimal::setTargetLocation(FVector location) {
	CurrentTargetLocation = location;
}

FVector AAnimal::getTargetLocation() {
	return CurrentTargetLocation;
}

