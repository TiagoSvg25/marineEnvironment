#include "Entities/Fish.h"
#include "Controllers/FishController.h"


AFish::AFish()
{
	FishMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FishMesh"));


	if (RootComponent)
	{
		FishMesh->SetupAttachment(RootComponent);
	}

	FishMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AIControllerClass = AFishController::StaticClass();

	if (FloatingMovement)
	{
		FloatingMovement->SetUpdatedComponent(RootComponent);
	}
}

AFish::~AFish()
{
}

void AFish::BeginPlay()
{
	Super::BeginPlay();

	if (!FishMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("FishMesh is null!"));
		return;
	}

	FishMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);

	if (Anim && GetClass() == AFish::StaticClass())
	{
		FishMesh->PlayAnimation(Anim, true);
	}
	else UE_LOG(LogTemp, Error, TEXT("Animation is null! Check the asset path."));

	setState("Idle");

	setEnergyThreshold(FMath::RandRange(20.0f, 40.0f));

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