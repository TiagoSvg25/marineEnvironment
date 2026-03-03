// Fill out your copyright notice in the Description page of Project Settings.


#include "Organism.h"

// Sets default values
AOrganism::AOrganism()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;

}


void AOrganism::setPhysicalCharacteristics(float NewSize, float NewHeight, float NewWeight)
{
	Physical.Size = NewSize;
	Physical.Height = NewHeight;
	Physical.Weight = NewWeight;
}

void AOrganism::setEnvironmentalCharacteristics(EcoClass Ecotype, float NewMinDepth, float NewMaxDepth)
{
	Environmental.EcoType = Ecotype;
	Environmental.MinDepth = NewMinDepth;
	Environmental.MaxDepth = NewMaxDepth;
}

void AOrganism::setMovementCharacteristics(float NewSpeed, float NewRadiusAwareness, float NewAngleVision)
{
	Movement.Speed = NewSpeed;
	Movement.AwarenessRadius = NewRadiusAwareness;
	Movement.AngleVision = NewAngleVision;
}

void AOrganism::setOrganismMeshe(USkeletalMesh* meshe, UAnimSequence* anims)
{
	SphereMesh->SetSkeletalMesh(meshe);
	this->anim = anims;
}


void AOrganism::updateMovement(float DeltaTime)
{
	FVector getActorLocation = GetActorLocation();
	FVector newLocation = getActorLocation + FVector(Movement.Speed * DeltaTime, 0.0f, 0.0f);
	SetActorLocation(newLocation);
}


// Called when the game starts or when spawned
void AOrganism::BeginPlay()
{
	Super::BeginPlay();
	SphereMesh->PlayAnimation(anim, true);
}

// Called every frame
void AOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	updateMovement(DeltaTime);

}

