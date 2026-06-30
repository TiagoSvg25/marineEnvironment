// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Plant/Algae.h"
#include "Entities/Plant/Plant.h"
#include "Controllers/Plant/AlgaeController.h"

AAlgae::AAlgae()
{
	if (RootComponent)
	{
		MeshAsset->SetupAttachment(RootComponent);
	}

	// TO BE CHANGED
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/seaweed_skeletal_mesh.seaweed_skeletal_mesh'"));

	if (SphereAsset.Succeeded())
	{
		MeshAsset->SetSkeletalMesh(SphereAsset.Object);
	}

	float scale = FMath::RandRange(1, 3);

	AIControllerClass = AAlgaeController::StaticClass();

	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f) * scale);

	MeshAsset->SetRelativeScale3D(FVector(scale, scale, scale));
}

AAlgae::~AAlgae()
{
}

void AAlgae::BeginPlay()
{
	Super::BeginPlay();

	setState("Idle");

	setEnergy(FMath::RandRange(1.0f, 50.0f));

	setEnergyGainRate(0.07f);
}

void AAlgae::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}