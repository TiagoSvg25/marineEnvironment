// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Fish/ClownFish.h"



AClownFish::AClownFish()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));

	MeshAsset->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	if (SphereAsset.Succeeded())
	{
		MeshAsset->SetSkeletalMesh(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		anim = Animation.Object;

	}

	bIsPredator = false;
}


void AClownFish::BeginPlay()
{
	Super::BeginPlay();

	MeshAsset->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));

	setSpeed(0.3f);

	setBaseSpeed(0.3f);

	setEnergyThreshold(50.0f);

	setEnergy(60.f);

	setState("Idle");

	setAwarenessRadius(10000.f);

	setAngleVision(70.f);

	setDirectionChangeInterval(3.f);

	MeshAsset->PlayAnimation(anim, true);
}