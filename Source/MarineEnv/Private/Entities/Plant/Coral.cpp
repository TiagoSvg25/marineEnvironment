// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Plant/Coral.h"
#include "Entities/Plant/Plant.h"
#include "Controllers/Plant/CoralController.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

ACoral::ACoral()
{


	if (RootComponent)
	{
		MeshAsset->SetupAttachment(RootComponent);
	}


	// TO BE CHANGED - NEED TO IMPLEMENT SKELETON AND ANIMATION
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/seaweed_skeletal_mesh.seaweed_skeletal_mesh'"));


	if (SphereAsset.Succeeded())
	{
		MeshAsset->SetSkeletalMesh(SphereAsset.Object);
	}

	float scale = FMath::RandRange(1, 3);

	AIControllerClass = ACoralController::StaticClass();

	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f) * scale);

	MeshAsset->SetRelativeScale3D(FVector(scale, scale, scale));

	BubbleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BubbleComponent"));

	if (MeshAsset)
	{
		BubbleComponent->SetupAttachment(MeshAsset);
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BubbleAsset(TEXT(" / Script / Niagara.NiagaraSystem'/Game/VFX/Bubbles.Bubbles'"));

	if (BubbleAsset.Succeeded())
	{
		BubbleComponent->SetAsset(BubbleAsset.Object);
	}

	SetBubblesActive(true);

}

ACoral::~ACoral()
{
}

void ACoral::BeginPlay()
{
	Super::BeginPlay();


	setState("Idle");

	setEnergy(50.0f);

}

void ACoral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoral::SetBubblesActive(bool bActive)
{
	if (BubbleComponent)
	{
		if (bActive) BubbleComponent->Activate();
		else BubbleComponent->Deactivate();
	}
}