#include "Entities/Fish/Fish.h"
#include "Controllers/Fish/FishController.h"


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

	ShoalSubsystem = GetWorld()->GetSubsystem<UShoalManager>();


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
