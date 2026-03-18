// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Organism.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Controllers/OrganismAIController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOrganism::AOrganism()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(16.f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetCollisionObjectType(ECC_Pawn);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);	

	AIControllerClass = AOrganismAIController::StaticClass();
}

float AOrganism::getHealth() const
{
	return getDataAsset()->Health;
}

void AOrganism::setHealth(float NewHealth)
{
	getDataAsset()->Health = NewHealth;

}

int AOrganism::getAge() const
{
	return getDataAsset()->Age;
}

void AOrganism::setAge(int NewAge)
{
	getDataAsset()->Age = NewAge;
}

int AOrganism::getAgeReproduction() const
{
	return getDataAsset()->AgeReproduction;
}

void AOrganism::setAgeReproduction(int NewAgeReproduction)
{
	getDataAsset()->AgeReproduction = NewAgeReproduction;
}

int AOrganism::getScale() const
{
	return getDataAsset()->Scale;
}

void AOrganism::setScale(int NewScale)
{
	getDataAsset()->Scale = NewScale;
}

float AOrganism::getSpawnDensity() const
{
	return getDataAsset()->SpawnDensity;
}

void AOrganism::setSpawnDensity(float NewSpawnDensity)
{
	getDataAsset()->SpawnDensity = NewSpawnDensity;
}

float AOrganism::getMinDepthRange() const
{
	return getDataAsset()->MinDepthRange;
}

float AOrganism::getMaxDepthRange() const
{
	return getDataAsset()->MaxDepthRange;
}

void AOrganism::setMinDepthRange(float NewMinDepthRange)
{
	getDataAsset()->MinDepthRange = NewMinDepthRange;
}

void AOrganism::setMaxDepthRange(float NewMaxDepthRange)
{
	getDataAsset()->MaxDepthRange = NewMaxDepthRange;
}

USkeletalMesh* AOrganism::getMeshAsset() const
{
	return getDataAsset()->MeshAsset;
}

void AOrganism::setMeshAsset(USkeletalMesh* NewMeshAsset)
{
	getDataAsset()->MeshAsset = NewMeshAsset;
}

UAnimSequence* AOrganism::getAnimAsset() const
{
	return getDataAsset()->anim;
}

void AOrganism::setAnimAsset(UAnimSequence* NewAnimAsset)
{
	UAnimSequence* AnimAsset = getDataAsset()->anim;
}



TArray<FString> AOrganism::getTags() const {
	return getDataAsset()->Tags;
}

void AOrganism::setTags(const TArray<FString>& NewTags)
{
	getDataAsset()->Tags = NewTags;
}











/*void AOrganism::updateMovement(float DeltaTime)
{
	// first phase - calculate the direction to the organism move

	CurrentDirection = FMath::VInterpTo(CurrentDirection, TargetDirection, DeltaTime, Movement.TurnSpeed);

	AddMovementInput(CurrentDirection, Movement.Speed);

	if (CurrentDirection.SizeSquared() > KINDA_SMALL_NUMBER)
	{
		FRotator TargetRotation = CurrentDirection.ToOrientationRotator();
		FRotator Smoothed = FMath::RInterpTo(
			GetActorRotation(),
			TargetRotation,
			DeltaTime,
			Movement.TurnSpeed
		);
		SetActorRotation(Smoothed);
	}
} */

// Called when the game starts or when spawned


	/*CurrentDirection = FMath::VRand();
	DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);
	DetectionInterval = FMath::RandRange(1.0f, 1.5f);
	calculateVectors();
	SphereMesh->PlayAnimation(anim, true);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOrganism::OnOrganismOverlap);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AOrganism::OnHitTerrain);*/




/*
void AOrganism::OnOrganismOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AOrganism* Other = Cast<AOrganism>(OtherActor);
	if (!Other) return;

	// notify controller
	AOrganismAIController* MyController = Cast<AOrganismAIController>(GetController());
	if (MyController)
		MyController->onActorCollision(Other);
}

void AOrganism::OnHitTerrain(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	// reflect direction off the terrain normal
	AOrganismAIController* MyController = Cast<AOrganismAIController>(GetController());
	if (MyController)
		MyController->onTerrainCollision(Hit.Normal);
}
*/
