#include "Entities/Fish.h"
#include "Controllers/FishController.h"


AFish::AFish()
{
	 
	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FishMesh"));
	RootComponent = FishMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereAsset.Succeeded())
	{
		FishMesh->SetStaticMesh(SphereAsset.Object);
	}

	AIControllerClass = AFishController::StaticClass();

	if (FloatingMovement)
	{
		FloatingMovement->SetUpdatedComponent(RootComponent);
	}

	setTrophicLevel(bIsPredator ? 2 : 1);

}

AFish::~AFish()
{
}

void AFish::BeginPlay()
{
	Super::BeginPlay();


	setState("Idle");

	setEnergyThreshold(FMath::RandRange(20.0f, 40.0f));

	setAwarenessRadius(FMath::RandRange(10.0f, 15.0f));

	setTrophicLevel(bIsPredator ? 2 : 1);

	setSpeed(1.0f);
}

void AFish::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}




/*
void AFish::updateMovement(float DeltaTime)
{

	// first phase - calculate the direction to the organism move

	CurrentDirection = FMath::VInterpTo(CurrentDirection, CurrentDirection, DeltaTime, AnimalDataAsset->DirectionChangeInterval);

	AddMovementInput(CurrentDirection, AnimalDataAsset->Speed);

	if (CurrentDirection.SizeSquared() > KINDA_SMALL_NUMBER)
	{
		FRotator TargetRotation = CurrentDirection.ToOrientationRotator();
		FRotator Smoothed = FMath::RInterpTo(
			GetActorRotation(),
			TargetRotation,
			DeltaTime,
			AnimalDataAsset->DirectionChangeInterval
		);
		SetActorRotation(Smoothed);
	}
}*/