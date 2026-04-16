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

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(50.f, 20.f, 15.f));

	MeshAsset = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshAsset"));

	//MeshAsset->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//MeshAsset->SetGenerateOverlapEvents(true);
	//MeshAsset->SetCollisionObjectType(ECC_Pawn);
	//MeshAsset->SetNotifyRigidBodyCollision(true);
	//MeshAsset->SetCollisionResponseToAllChannels(ECR_Ignore);
	//MeshAsset->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	//MeshAsset->OnComponentBeginOverlap.AddDynamic(this, &AOrganism::OnOrganismOverlap);
	//MeshAsset->OnComponentHit.AddDynamic(this, &AOrganism::OnHitTerrain);


	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionBox->SetCollisionObjectType(ECC_Pawn);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AOrganism::OnOrganismOverlap);
	CollisionBox->OnComponentHit.AddDynamic(this, &AOrganism::OnHitTerrain);


	AIControllerClass = AOrganismAIController::StaticClass();
}

void AOrganism::OnOrganismOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{


	if (OverlappedComp != CollisionBox) return;

	
	AOrganism* Other = Cast<AOrganism>(OtherActor);
	if (!Other) return;

	AOrganismAIController* MyController = Cast<AOrganismAIController>(GetController());
	if (MyController)
		MyController->onActorCollision(Other);

	UE_LOG(LogTemp, Warning, TEXT("%s Other Actor %s"), *GetName(), *OtherActor->GetName());
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



float AOrganism::getHealth() const
{
	return Health;
}

void AOrganism::setHealth(float NewHealth)
{
	Health = NewHealth;

}

int AOrganism::getAge() const
{
	return Age;
}

void AOrganism::setAge(int NewAge)
{
	Age = NewAge;
}


int AOrganism::getScale() const
{
	return Scale;
}

void AOrganism::setScale(int NewScale)
{
	Scale = NewScale;
}

float AOrganism::getSpawnDensity() const
{
	return SpawnDensity;
}

void AOrganism::setSpawnDensity(float NewSpawnDensity)
{
	SpawnDensity = NewSpawnDensity;
}

float AOrganism::getMinDepthRange() const
{
	return MinDepthRange;
}

float AOrganism::getMaxDepthRange() const
{
	return MaxDepthRange;
}

void AOrganism::setMinDepthRange(float NewMinDepthRange)
{
	MinDepthRange = NewMinDepthRange;
}

void AOrganism::setMaxDepthRange(float NewMaxDepthRange)
{
	MaxDepthRange = NewMaxDepthRange;
}

USkeletalMeshComponent* AOrganism::getMeshAsset() const
{
	return MeshAsset;
}

void AOrganism::setMeshAsset(USkeletalMeshComponent* NewMeshAsset)
{
	MeshAsset = NewMeshAsset;
}

UAnimSequence* AOrganism::getAnimAsset() const
{
	return anim;
}

void AOrganism::setAnimAsset(UAnimSequence* NewAnimAsset)
{
	UAnimSequence* AnimAsset = anim;
}



TArray<FString> AOrganism::getTags() const {
	return Tags;
}

void AOrganism::setTags(const TArray<FString>& NewTags)
{
	Tags = NewTags;
}

void AOrganism::addTag(const FString& NewTag)
{
	Tags.Add(NewTag);
}


FString AOrganism::getCurrentState() const
{
	return CurrentState;
}

void AOrganism::setState(const FString& NewState)
{
	CurrentState = NewState;
}

float AOrganism::getEnergy() const {
	return Energy;
}

void AOrganism::setEnergy(float NewEnergy) {
	Energy = NewEnergy;
}


float AOrganism::getEnergyThreshold() const
{
	return EnergyThreshold;
}

void AOrganism::setEnergyThreshold(float NewEnergyThreshold)
{
	EnergyThreshold = NewEnergyThreshold;
}

float AOrganism::getMaxEnergy() const
{
	return MaxEnergy;
}

void AOrganism::setMaxEnergy(float NewMaxEnergy)
{
	MaxEnergy = NewMaxEnergy;
}



float AOrganism::getEnergyConsumptionRate() const
{
	return EnergyConsumptionRate;
}

void AOrganism::setEnergyConsumptionRate(float NewEnergyConsumptionRate)
{
	EnergyConsumptionRate = NewEnergyConsumptionRate;
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
