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

void AOrganism::setEnvironmentalCharacteristics(EcoClass Ecotype, int NewTrophicLevel,float NewMinDepth, float NewMaxDepth)
{
	Environmental.EcoType = Ecotype;
	Environmental.TrophicLevel = NewTrophicLevel;
	Environmental.MinDepth = NewMinDepth;
	Environmental.MaxDepth = NewMaxDepth;
}

void AOrganism::setMovementCharacteristics(float NewSpeed, MovementState NewState, float NewRadiusAwareness,float NewTurnSpeed, float NewAngleVision)
{
	Movement.Speed = NewSpeed;
	Movement.InitialState = NewState;
	Movement.AwarenessRadius = NewRadiusAwareness;
	Movement.TurnSpeed = NewTurnSpeed;	
	Movement.AngleVision = NewAngleVision;
}

void AOrganism::setOrganismMeshe(USkeletalMesh* meshe, UAnimSequence* anims)
{
	SphereMesh->SetSkeletalMesh(meshe);
	this->anim = anims;
}

void AOrganism::activateDetection(float DeltaTime)
{
	if (DetectionTimer >= DetectionInterval) {
		DetectionTimer = 0.0f;
		BehaviourAnalisys();
	}
}

void AOrganism::updateMovement(float DeltaTime)
{
	// first phase - calculate the direction to the organism move

	CurrentDirection = FMath::VInterpTo(CurrentDirection, TargetDirection, DeltaTime, Movement.TurnSpeed);

	if (DirectionTimer >= DirectionChangeInterval) {
		calculateVectors();
	}

	// secod phase - move the organism in the direction calculated in the first phase
	NewRotation = FRotationMatrix::MakeFromZ(CurrentDirection).Rotator();
	SetActorRotation(NewRotation);
	FVector NewLocation = GetActorLocation() + (CurrentDirection * Movement.Speed * DeltaTime);
	SetActorLocation(NewLocation);

} 

// Called when the game starts or when spawned
void AOrganism::BeginPlay()
{
	Super::BeginPlay();

	CurrentDirection = FMath::VRand();	
	DirectionChangeInterval = FMath::RandRange(2.0f, 5.0f);
	DetectionInterval = FMath::RandRange(2.0f, 5.0f);

	NewRotation = FRotationMatrix::MakeFromZ(CurrentDirection).Rotator();
	NewRotation.Pitch += 180.0f;
	calculateVectors();
	SphereMesh->PlayAnimation(anim, true);



}

// Called every frame
void AOrganism::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DirectionTimer += DeltaTime;
	DetectionTimer += DeltaTime;

	activateDetection(DeltaTime);
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

