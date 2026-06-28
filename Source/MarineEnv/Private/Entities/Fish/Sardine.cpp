// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Fish/Sardine.h"
#include "Controllers/Fish/FlockingController.h"


ASardine::ASardine()
{
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(
        TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Sardine/Sardine.Sardine'"));

    static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(
        TEXT("/Script/Engine.AnimSequence'/Game/Assets/Sardine/Sardine_Anim.Sardine_Anim'"));

    if (!MeshAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("MeshAsset is null in Sardine constructor!"));
        return;
    }

    if (SphereAsset.Succeeded())
        MeshAsset->SetSkeletalMesh(SphereAsset.Object);
    else
        UE_LOG(LogTemp, Error, TEXT("SkeletalMesh not found!"));

    if (Animation.Succeeded())
        anim = Animation.Object;
    else
        UE_LOG(LogTemp, Error, TEXT("Animation not found!"));

    MeshAsset->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    AIControllerClass = AFlockingController::StaticClass();
    bIsPredator = false;
}

void ASardine::BeginPlay()
{
	Super::BeginPlay();

    SetActorRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

    MeshAsset->SetSimulatePhysics(false);
    MeshAsset->SetEnablePhysicsBlending(false);

	setState("Idle");

	setTrophicLevel(1);

	setSpeed(0.5f);
	setBaseSpeed(0.5f);

    setEnergy(60.f);

	setEnergyThreshold(90.0f);

	setEnergyConsumptionRate(0.4f);

	setAwarenessRadius(2000.0f);

	setAngleVision(120.0f);

	setTurnSpeed(3.0f);

	setDirectionChangeInterval(15.0f);
    setMaxShoals(30);
	addTag("Sardine");
	addTag("Schooling");
}

void ASardine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
