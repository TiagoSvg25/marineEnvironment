// Fill out your copyright notice in the Description page of Project Settings.

#include "Shark.h"



AShark::AShark()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SharkMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Character/Shark/Shark.Shark'"));

	if (SharkMesh.Succeeded()) {
		FishMesh->SetSkeletalMesh(SharkMesh.Object);
	}

	else UE_LOG(LogTemp, Error, TEXT("ERRO: Nao foi possivel encontrar a mesh do tubarao no caminho especificado!"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> SwimAsset(TEXT("/Script/Engine.AnimSequence'/Game/Character/Shark/Animations/Sharkmetarig_Swim_Shark.Sharkmetarig_Swim_Shark'"));

	if (SwimAsset.Succeeded())
		AnimSwim = SwimAsset.Object;

	else UE_LOG(LogTemp, Error, TEXT("ERRO: Nao foi possivel encontrar a animacao de nado!"));

	AIControllerClass = ASharkController::StaticClass();

}


void AShark::BeginPlay()
{
	Super::BeginPlay();
	FishMesh->SetRelativeLocationAndRotation(FVector(-150.0f, 0.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));


	bUseControllerRotationYaw = false;

	setSpeed(1.5f);

	setEnergyThreshold(30.0f);

	setEnergyConsumptionRate(0.3f);

	setAwarenessRadius(1500.0f);

	setAngleVision(60.0f);

	setTrophicLevel(3);

	setTurnSpeed(1.5f);

	setDirectionChangeInterval(8.0f);

	if (FishMesh && AnimSwim) {

		FishMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);

		FishMesh->PlayAnimation(AnimSwim, true);

		FishMesh->SetPlayRate(0.8f);
	}
}