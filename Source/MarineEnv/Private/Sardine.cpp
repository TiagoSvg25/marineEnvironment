// Fill out your copyright notice in the Description page of Project Settings.


#include "Sardine.h"

ASardine::ASardine()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));


	if (SphereAsset.Succeeded())
	{
		MeshAsset->SetSkeletalMesh(SphereAsset.Object);
		//setMeshAsset(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		anim = Animation.Object;

	}

	bIsPredator = false;
}

void ASardine::BeginPlay()
{
	Super::BeginPlay();

	MeshAsset->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));

	setState("Idle");

	MeshAsset->PlayAnimation(anim, true);

	setTrophicLevel(1);

	setSpeed(1.0f);

	setEnergyThreshold(50.0f);

	setEnergyConsumptionRate(0.4f);

	setAwarenessRadius(1000.0f);

	setAngleVision(60.0f);

	setTurnSpeed(1.0f);

	setDirectionChangeInterval(10.0f);

	addTag("Sardine");
	addTag("Schooling");
}

void ASardine::Tick(float DeltaTime)
{
}
