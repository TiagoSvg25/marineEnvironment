// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingController.h"


AFlockingController::AFlockingController()
{

}

void AFlockingController::flockingBehaviour()
{
	if (getModel()->getNeighbors().Num() == 0) return;

	alignWithNeighbors();
	cohesionWithNeighbors();
	separateFromNeighbors();

	FVector FlockingForce = AlignmentVector.GetSafeNormal() * AlignWeight + CohesionVector.GetSafeNormal() * CohesionWeight + SeparationVector.GetSafeNormal() * SeparationWeight;

	getModel()->setTargetLocation(getModel()->GetActorLocation() + FlockingForce * 100.0f);

}

void AFlockingController::alignWithNeighbors()
{

	FVector AverageDirection = FVector::ZeroVector;

	for (AFish* neighborFish : getModel()->getNeighbors()) {
		AverageDirection += neighborFish->getTargetLocation();
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

	if (getModel()->getCurrentState() == "Idle") {
		for (auto fishTags : getModel()->getTags()) {
			UE_LOG(LogTemp, Warning, TEXT(""));
		}

		UE_LOG(LogTemp, Warning, TEXT("A procurar vizinhos com tags..."));

		float oldAngle = getModel()->getAngleVision();
		getModel()->setAngleVision(360.f);
		AAnimal* animal = Cast<AAnimal>(find(AFish::StaticClass(), getModel()->getTags(), true, -1, -1));
		getModel()->setAngleVision(oldAngle);
		UE_LOG(LogTemp, Warning, TEXT("Resultado find: %s"), animal ? TEXT("encontrou") : TEXT("nao encontrou"));

		if (animal != nullptr) {

			getModel()->setState("Flocking");

			UE_LOG(LogTemp, Warning, TEXT("Found neighbor for flocking"));

			getModel()->getShoalSubsystem()->AddShoal(Cast<AFish>(getModel()));
		}
	}


	else if (getModel()->getCurrentState() == "Flocking") {
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

	Super::BehaviourAnalisys(DeltaTime);
}