// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Fish/DoryFish.h"

ADoryFish::ADoryFish()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Fish/Dory.Dory'"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/Fish/Dory_Anim.Dory_Anim'"));

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

	MeshAsset->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	bIsPredator = false;
}


void ADoryFish::BeginPlay()
{
	Super::BeginPlay();

	setTrophicLevel(1);

	setSpeed(0.3f);

	setBaseSpeed(0.3f);

	setEnergyThreshold(80.0f);

	setEnergy(60.f);

	setState("Idle");

	setAwarenessRadius(10000.f);

	setAngleVision(70.f);

	setDirectionChangeInterval(3.f);

	MeshAsset->PlayAnimation(anim, true);
}