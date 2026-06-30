// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/Fish/Shark.h"



AShark::AShark()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SharkMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Shark/Bob.Bob'"));

	if (SharkMesh.Succeeded()) {
		MeshAsset->SetSkeletalMesh(SharkMesh.Object);
	}
	else UE_LOG(LogTemp, Error, TEXT("ERRO: Nao foi possivel encontrar a mesh do tubarao no caminho especificado!"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> SwimAsset(TEXT("/Script/Engine.AnimSequence'/Game/Assets/Shark/Bob_Anim.Bob_Anim'"));

	MeshAsset->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionBox->SetBoxExtent(FVector(450.f, 80.f, 100.f));

	if (SwimAsset.Succeeded())
		anim = SwimAsset.Object;

	else UE_LOG(LogTemp, Error, TEXT("ERRO: Nao foi possivel encontrar a animacao de nado!"));

	AIControllerClass = ASharkController::StaticClass();


	bIsPredator = true;

}


void AShark::BeginPlay()
{
	Super::BeginPlay();
	MeshAsset->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));
	bUseControllerRotationYaw = false;

	setSpeed(0.7f);

	setBaseSpeed(0.7f);

	setEnergy(50.f);

	setMaxEnergy(130.f);

	setEnergyThreshold(70.0f);

	setEnergyConsumptionRate(0.5f);

	setAwarenessRadius(1500.0f);

	setAngleVision(60.0f);

	setTrophicLevel(3);

	setTurnSpeed(1.0f);

	setDirectionChangeInterval(8.0f);

	if (MeshAsset && anim) {

		MeshAsset->SetAnimationMode(EAnimationMode::AnimationSingleNode);

		MeshAsset->PlayAnimation(anim, true);

		MeshAsset->SetPlayRate(1.f);
	}
}