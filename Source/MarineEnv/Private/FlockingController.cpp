// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingController.h"



void AFlockingController::flockingBehaviour()
{
	if (getModel()->getNeighbors().Num() == 0) return;

	alignWithNeighbors();
	cohesionWithNeighbors();
	separateFromNeighbors();

	getModel()->setTargetLocation(getModel()->GetActorLocation() + AlignmentVector + CohesionVector + SeparationVector);
}

void AFlockingController::alignWithNeighbors()
{

	FVector AverageDirection = FVector::ZeroVector;

	for (AFish* neighborFish : getModel()->getNeighbors()) {
		AverageDirection += neighborFish->GetTargetLocation();
	}

	AlignmentVector = AverageDirection / getModel()->getNeighbors().Num();

}

void AFlockingController::cohesionWithNeighbors()
{
	FVector CenterOfMass = FVector::ZeroVector;

	for (AFish* fish : getModel()->getNeighbors()) {
		CenterOfMass += fish->GetActorLocation();
	}

	CohesionVector = (CenterOfMass / getModel()->getNeighbors().Num()) - getModel()->GetActorLocation();
	
}

void AFlockingController::separateFromNeighbors()
{
	FVector DistanceNeighbors = FVector::ZeroVector;
	for (AFish* neighbor : getModel()->getNeighbors()){
		float Distance = FVector::Dist(getModel()->GetActorLocation(), neighbor->GetActorLocation());
		if (Distance < SeparationDistance) {
			DistanceNeighbors += (getModel()->GetActorLocation() - neighbor->GetActorLocation()) / Distance;
		}
	}

	SeparationVector = DistanceNeighbors;
}



void AFlockingController::BehaviourAnalisys(float DeltaTime)
{
	Super::BehaviourAnalisys(DeltaTime);

	if (getModel()->getCurrentState() == "Idle") {
		AAnimal* animal = Cast<AAnimal>(find(AFish::StaticClass(), getModel()->getTags(), true, -1,-1));

		if (animal != nullptr) {

			 getModel()->setState("Flocking");

			 UE_LOG(LogTemp, Warning, TEXT("Found neighbor for flocking"));

			 getModel()->getShoalSubsystem()->AddShoal(Cast<AFish>(getModel()));
		}
	}


	if (getModel()->getCurrentState() == "Flocking") {
		AAnimal* pred = Cast<AAnimal>(find(AAnimal::StaticClass(), {}, false, -1, getModel()->getTrophicLevel() + 1));

		if (pred != nullptr) {

			getModel()->getShoalSubsystem()->RemoveShoal(Cast<AFish>(getModel()), getModel()->getShoalId());
			
			getModel()->setShoalId("");
			getModel()->setNeighbors(TArray<AFish*>());
			getModel()->setState("Fleeing");
			return;
		}

		flockingBehaviour();
		updateMovement(DeltaTime);
	}
}