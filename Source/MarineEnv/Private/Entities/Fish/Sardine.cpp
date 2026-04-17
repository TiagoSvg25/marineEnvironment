// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Fish/Sardine.h"
#include "Controllers/Fish/FlockingController.h"


ASardine::ASardine()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));


	if (SphereAsset.Succeeded())
	{
		MeshAsset->SetSkeletalMesh(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		anim = Animation.Object;

	}

	AIControllerClass = AFlockingController::StaticClass();

	bIsPredator = false;
}

void ASardine::BeginPlay()
{
	Super::BeginPlay();

	MeshAsset->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));

	setState("Idle");

	MeshAsset->PlayAnimation(anim, true);

	setTrophicLevel(1);

	setSpeed(0.5f);
	setBaseSpeed(0.5f);

	setEnergyThreshold(90.0f);

	setEnergyConsumptionRate(0.4f);

	setAwarenessRadius(2000.0f);

	setAngleVision(120.0f);

	setTurnSpeed(3.0f);

	setDirectionChangeInterval(15.0f);

	addTag("Sardine");
	addTag("Schooling");
}

void ASardine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
