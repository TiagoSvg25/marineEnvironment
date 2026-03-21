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

	AlgaeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ECollisionEnabled::QueryAndPhysics
	AlgaeMesh->SetCollisionObjectType(ECC_Pawn);
	AlgaeMesh->SetCollisionResponseToAllChannels(ECR_Block);
	AlgaeMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// TO BE CHANGED
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));


	if (SphereAsset.Succeeded())
	{
		AlgaeMesh->SetSkeletalMesh(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		Anim = Animation.Object;
	}

	AIControllerClass = AAlgaeController::StaticClass();
}

AAlgae::~AAlgae()
{
}

void AAlgae::BeginPlay()
{
	Super::BeginPlay();

	if (!AlgaeMesh)
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
		AlgaeMesh->PlayAnimation(Anim, true);
		UE_LOG(LogTemp, Warning, TEXT("Animation started successfully"));
	}

	AlgaeMesh->PlayAnimation(Anim, true);

	setState("Idle");

	setEnergy(50.0f);


}

void AAlgae::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}