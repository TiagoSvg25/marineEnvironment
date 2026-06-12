// Fill out your copyright notice in the Description page of Project Settings.


#include "entities/Fish/SeaHorse.h"

// Fill out your copyright notice in the Description page of Project Settings.

ASeaHorse::ASeaHorse()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/SeaHorse/SeaHorse.SeaHorse'"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/SeaHorse/SeaHorse_Anim.SeaHorse_Anim'"));

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

	MeshAsset->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	bIsPredator = false;
}


void ASeaHorse::BeginPlay()
{
	Super::BeginPlay();

	setSpeed(0.3f);

	setBaseSpeed(0.3f);

	setEnergyThreshold(80.0f);

	setEnergy(60.f);

	setState("Idle");

	setAwarenessRadius(10000.f);
	

	setAngleVision(70.f);

	setScale(0.5);
	setDirectionChangeInterval(10.f);

	
	MeshAsset->PlayAnimation(anim, true);
}