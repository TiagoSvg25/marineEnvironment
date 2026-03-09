// Fill out your copyright notice in the Description page of Project Settings.


#include "Organism.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "OrganismAIController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOrganism::AOrganism()
{

	PrimaryActorTick.bCanEverTick = true;

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	AutoPossessAI = EAutoPossessAI::Disabled;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	SphereMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SphereMesh"));

	AIControllerClass = AOrganismAIController::StaticClass();


	RootComponent = SphereMesh;

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

	if (DirectionTimer >= DirectionChangeInterval) {
		calculateVectors();
	}
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
	DetectionInterval = FMath::RandRange(2.0f, 5.0f);
	calculateVectors();
	SphereMesh->PlayAnimation(anim, true);
}

// Called every frame
void AOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DirectionTimer += DeltaTime;
	DetectionTimer += DeltaTime;

	updateMovement(DeltaTime);

}

void AOrganism::calculateVectors()
{
	DirectionTimer = 0.0f;
	TargetDirection = FMath::VRand();
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

