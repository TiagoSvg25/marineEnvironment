// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Fish/Tuna.h"
#include "Controllers/Fish/FlockingController.h"


ATuna::ATuna()
{
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereAsset(
        TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Tuna/Tuna.Tuna'"));

    static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(
        TEXT("/Script/Engine.AnimSequence'/Game/Assets/Tuna/Tuna_Anim.Tuna_Anim'"));

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

    MeshAsset->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

    AIControllerClass = AFlockingController::StaticClass();
    bIsPredator = false;
}

void ATuna::BeginPlay()
{
    Super::BeginPlay();


    MeshAsset->SetSimulatePhysics(false);
    MeshAsset->SetEnablePhysicsBlending(false);

    setState("Idle");

    setTrophicLevel(2);
    
    setSpeed(0.5f);
    setBaseSpeed(0.5f);

    setEnergyThreshold(90.0f);

    setEnergyConsumptionRate(0.4f);

    setAwarenessRadius(2000.0f);
    setMaxShoals(15);
    setAngleVision(120.0f);

    setTurnSpeed(3.0f);

    setDirectionChangeInterval(15.0f);

    addTag("Tuna");
    addTag("Schooling");
}

void ATuna::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
