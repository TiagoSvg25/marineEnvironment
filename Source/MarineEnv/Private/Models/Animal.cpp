#include "Entities/Animal.h"
#include "Controllers/AnimalAIController.h"



AAnimal::AAnimal()
{

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	
	if (FloatingMovement && RootComponent)
	{
		FloatingMovement->SetUpdatedComponent(RootComponent);
	}



	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAnimalAIController::StaticClass();
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	setState("Idle");
	setEnergy(getMaxEnergy());
	setSpeed(getBaseSpeed());
	setTargetLocation(GetActorLocation());
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

float AAnimal::getAwarenessRadius() const
{
	return AwarenessRadius;
}

void AAnimal::setAwarenessRadius(float NewAwarenessRadius)
{
	AwarenessRadius = NewAwarenessRadius;
}

float AAnimal::getAngleVision() const
{
	return AngleVision;
}

void AAnimal::setAngleVision(float NewAngleVision)
{
	AngleVision = NewAngleVision;
}

int AAnimal::getTrophicLevel() const
{
	return TrophicLevel;
}

void AAnimal::setTrophicLevel(int NewTrophicLevel)
{
	TrophicLevel = NewTrophicLevel;
}

float AAnimal::getDirectionChangeInterval() const
{
	return DirectionChangeInterval;
}

void AAnimal::setDirectionChangeInterval(float NewDirectionChangeInterval)
{
	DirectionChangeInterval = NewDirectionChangeInterval;
}



float AAnimal::getSpeed() const
{
	return Speed;
}

void AAnimal::setSpeed(float NewSpeed)
{
	Speed = NewSpeed;
}

float AAnimal::getEnergyThreshold() const
{
	return EnergyThreshold;
}

void AAnimal::setEnergyThreshold(float NewEnergyThreshold)
{
	EnergyThreshold = NewEnergyThreshold;
}

float AAnimal::getMaxEnergy() const
{
	return MaxEnergy;
}

void AAnimal::setMaxEnergy(float NewMaxEnergy)
{
	MaxEnergy = NewMaxEnergy;
}



float AAnimal::getEnergy() const {
	return Energy;
}

void AAnimal::setEnergy(float NewEnergy) {
	Energy = NewEnergy;
}


float AAnimal::getEnergyConsumptionRate() const
{
	return EnergyConsumptionRate;
}

void AAnimal::setEnergyConsumptionRate(float NewEnergyConsumptionRate)
{
	EnergyConsumptionRate = NewEnergyConsumptionRate;
}

float AAnimal::getTurnSpeed() const
{
	return TurnSpeed;
}


void AAnimal::setTurnSpeed(float NewTurnSpeed)
{
	TurnSpeed = NewTurnSpeed;
}

void AAnimal::setTargetLocation(FVector location) {
	CurrentTargetLocation = location;
}

FVector AAnimal::getTargetLocation() {
	return CurrentTargetLocation;
}

float AAnimal::getBaseSpeed() const {
	return BaseSpeed;
}
