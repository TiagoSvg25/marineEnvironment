#include "Fish.h"


AFish::AFish()
{
	CurrentDirection = FMath::VRand();

	AnimalDataAsset = CreateDefaultSubobject<UAnimalDataAsset>(TEXT("AnimalDataAsset"));  

	AnimalDataAsset->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes"));
	AnimalDataAsset->Mesh->SetupAttachment(RootComponent);


	AnimalDataAsset->DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);

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



void AFish::UpdateBehaviour()
{

}


void AFish::BehaviourAnalisys()
{

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