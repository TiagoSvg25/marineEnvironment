// Fill out your copyright notice in the Description page of Project Settings.


#include "Organism.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "OrganismAIController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOrganism::AOrganism()
{

	/*PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
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



	SphereMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(RootComponent);

	AIControllerClass = AOrganismAIController::StaticClass();

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->SetUpdatedComponent(RootComponent);*/
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
void AOrganism::BeginPlay()
{
	Super::BeginPlay();

	/*CurrentDirection = FMath::VRand();
	DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);
	DetectionInterval = FMath::RandRange(1.0f, 1.5f);
	calculateVectors();
	SphereMesh->PlayAnimation(anim, true);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOrganism::OnOrganismOverlap);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AOrganism::OnHitTerrain);*/
}

// Called every frame
void AOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


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
