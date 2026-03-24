// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Algae.h"
#include "Entities/Plant.h"
#include "Controllers/AlgaeController.h"

AAlgae::AAlgae()
{
	AlgaeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AlgaeMesh"));


	if (RootComponent)
	{
		AlgaeMesh->SetupAttachment(RootComponent);
	}


	// TO BE CHANGED
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/seaweed_skeletal_mesh.seaweed_skeletal_mesh'"));


	if (SphereAsset.Succeeded())
	{
		AlgaeMesh->SetSkeletalMesh(SphereAsset.Object);
	}

	float scale = FMath::RandRange(0.25, 0.75);

	AIControllerClass = AAlgaeController::StaticClass();
	AlgaeMesh->SetRelativeScale3D(FVector(scale, scale, scale));

}

AAlgae::~AAlgae()
{
}

void AAlgae::BeginPlay()
{
	Super::BeginPlay();


	setState("Idle");

	setEnergy(1.0f);


}

void AAlgae::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}