// Fill out your copyright notice in the Description page of Project Settings.


#include "Organism.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "OrganismAIController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOrganism::AOrganism()
{

	PrimaryActorTick.bCanEverTick = true;
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
	FloatingMovement->SetUpdatedComponent(RootComponent);
}


void AOrganism::setPhysicalCharacteristics(float NewSize, float NewHeight, float NewWeight)
{
	Physical.Size = NewSize;
	Physical.Height = NewHeight;
	Physical.Weight = NewWeight;
}

void AOrganism::setEnvironmentalCharacteristics(EcoClass Ecotype, int NewTrophicLevel,float NewMinDepth, float NewMaxDepth)
{
	Environmental.EcoType = Ecotype;
	Environmental.TrophicLevel = NewTrophicLevel;
	Environmental.MinDepth = NewMinDepth;
	Environmental.MaxDepth = NewMaxDepth;
}

FEnvironmentalCharacteristics AOrganism::getEnvironmentalCharacteristics() {
	return Environmental;
}


void AOrganism::setMovementCharacteristics(float NewSpeed, MovementState NewState, float NewRadiusAwareness,float NewTurnSpeed, float NewAngleVision)
{
	Movement.Speed = NewSpeed;
	Movement.InitialState = NewState;
	Movement.AwarenessRadius = NewRadiusAwareness;
	Movement.TurnSpeed = NewTurnSpeed;	
	Movement.AngleVision = NewAngleVision;
}

FMovementCharacteristics AOrganism::getMovementCharacteristics() {
	return Movement;
}


void AOrganism::setOrganismMeshe(USkeletalMesh* meshe, UAnimSequence* anims)
{
	SphereMesh->SetSkeletalMesh(meshe);
	this->anim = anims;
}


void AOrganism::setState(OrganismState NewState) {
	CurrentState = NewState;
}

OrganismState AOrganism::getState() {
	return CurrentState;
}



void AOrganism::updateMovement(float DeltaTime)
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
} 

// Called when the game starts or when spawned
void AOrganism::BeginPlay()
{
	Super::BeginPlay();

	CurrentDirection = FMath::VRand();	
	DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);
	DetectionInterval = FMath::RandRange(1.0f, 1.5f);
	calculateVectors();
	SphereMesh->PlayAnimation(anim, true);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOrganism::OnOrganismOverlap);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AOrganism::OnHitTerrain);
}

// Called every frame
void AOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrganism::calculateVectors()
{
	DirectionTimer = 0.0f;
	TargetDirection = FMath::VRand();
}

void AOrganism::OnOrganismOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AOrganism* Other = Cast<AOrganism>(OtherActor);
	if (!Other) return;

	// notify controller
	AOrganismAIController* MyController = Cast<AOrganismAIController>(GetController());
	if (MyController)
		MyController->onCatchPrey(Other);
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


void AOrganism::BehaviourAnalisys() {
	TArray<AActor*> OrganismsInArea;
	TArray<AActor*> OrganismsToIgnore;

	OrganismsToIgnore.Add(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool Found = UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetActorLocation(),
		Movement.AwarenessRadius,
		ObjectTypes,
		AOrganism::StaticClass(),
		OrganismsToIgnore,
		OrganismsInArea
	);

	AOrganism* ClosestOrganism = nullptr;
	double ClosestLocation = DOUBLE_BIG_NUMBER;

	if (Found) {
		for (AActor* Actor : OrganismsInArea) {
			AOrganism* Organism = Cast<AOrganism>(Actor);
			
			FVector OrganismLocation = Organism->GetActorLocation();

			double Result = FVector::Dist(GetActorLocation(), OrganismLocation);

			if (Result < ClosestLocation) {
				ClosestLocation = Result;
				ClosestOrganism = Organism;
			}

		}
	}

	if ( this->Environmental.TrophicLevel < ClosestOrganism->Environmental.TrophicLevel) {
		
	}
	else if (this->Environmental.TrophicLevel > ClosestOrganism->Environmental.TrophicLevel) {
		
	}
	
}


void AOrganism::UpdateBehaviour()
{

}

