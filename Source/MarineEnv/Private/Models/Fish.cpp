#include "Entities/Fish.h"
#include "Controllers/FishController.h"


AFish::AFish()
{
	FishMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FishMesh"));


	if (RootComponent)
	{
		FishMesh->SetupAttachment(RootComponent);
	}

	FishMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ECollisionEnabled::QueryAndPhysics
	/*FishMesh->SetCollisionObjectType(ECC_Pawn);
	FishMesh->SetCollisionResponseToAllChannels(ECR_Block);
	FishMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);*/

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));


	if (SphereAsset.Succeeded())
	{
		FishMesh->SetSkeletalMesh(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		Anim = Animation.Object;
	}

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

	if (!Anim)
	{
		UE_LOG(LogTemp, Error, TEXT("Animation is null! Check the asset path."));
	}
	else
	{
		FishMesh->PlayAnimation(Anim, true);
		UE_LOG(LogTemp, Warning, TEXT("Animation started successfully"));
	}

	FishMesh->PlayAnimation(Anim, true);

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