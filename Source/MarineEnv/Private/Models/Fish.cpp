#include "Entities/Fish.h"


AFish::AFish()
{
	 
	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FishMesh"));
	RootComponent = FishMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereAsset.Succeeded())
	{
		FishMesh->SetStaticMesh(SphereAsset.Object);
	}

	AnimalDataAsset->DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);

	CurrentDirection = FMath::VRand();


}

AFish::~AFish()
{
}

void AFish::BeginPlay()
{
	Super::BeginPlay();
}

void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BehaviourAnalisys();
}





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
}