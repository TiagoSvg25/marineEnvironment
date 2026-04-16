#include "Entities/Fish/Fish.h"
#include "Controllers/Fish/FishController.h"


AFish::AFish()
{


	if (RootComponent)
	{
		MeshAsset->SetupAttachment(RootComponent);
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

	ShoalSubsystem = GetWorld()->GetSubsystem<UShoalManager>();

	if (!MeshAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("FishMesh is null!"));
		return;
	}

	MeshAsset->SetAnimationMode(EAnimationMode::AnimationSingleNode);

	if (anim && GetClass() == AFish::StaticClass())
	{
		MeshAsset->PlayAnimation(anim, true);
	}
	else UE_LOG(LogTemp, Error, TEXT("Animation is null! Check the asset path."));

	setState("Idle");

	setEnergyThreshold(FMath::RandRange(20.0f, 40.0f));

}

void AFish::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}
