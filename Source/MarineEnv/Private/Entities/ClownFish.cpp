// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/ClownFish.h"




AClownFish::AClownFish()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(TEXT("/Game/Fab/Clown_Fish_Low_Poly_Animated/clown_fish_low_poly_animated/SkeletalMeshes/clown_fish_low_poly_animated.clown_fish_low_poly_animated"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT("/Script/Engine.AnimSequence'/Game/Assets/clown_fish_low_poly_animatedswim1.clown_fish_low_poly_animatedswim1'"));


	if (SphereAsset.Succeeded())
	{
		FishMesh->SetSkeletalMesh(SphereAsset.Object);
	}

	if (Animation.Succeeded())
	{
		Anim = Animation.Object;
	}

	bIsPredator = false;

}


void AClownFish::BeginPlay()
{
	Super::BeginPlay();

	FishMesh->PlayAnimation(Anim, true);
}