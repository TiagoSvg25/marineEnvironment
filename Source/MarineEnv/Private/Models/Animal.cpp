#include "Entities/Animal.h"
#include "Controllers/AnimalAIController.h"



AAnimal::AAnimal()
{

	DataAsset = CreateDefaultSubobject<UAnimalDataAsset>(TEXT("AnimalDataAsset"));
	// AAnimal.cpp ou AFish.cpp
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAnimalAIController::StaticClass();

}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = getDataAsset()->CurrentState;
}

void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




FString AAnimal::getCurrentState() const
{
	return getDataAsset()->CurrentState;
}

void AAnimal::setState(const FString& NewState)
{
	getDataAsset()->CurrentState = NewState;
}

bool AAnimal::isHunting() const
{
	return Hunting;
}

void AAnimal::setHunting(bool NewIsHunting)
{
	Hunting = NewIsHunting;
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
	return getDataAsset()->Speed;
}

void AAnimal::setSpeed(float NewSpeed)
{
	getDataAsset()->Speed = NewSpeed;
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
	return getDataAsset()->Energy;
}

void AAnimal::setEnergy(float NewEnergy) {
	getDataAsset()->Energy = NewEnergy;
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
	getDataAsset()->TargetLocation = location;
}

FVector AAnimal::getTargetLocation() {
	return getDataAsset()->TargetLocation;
}

