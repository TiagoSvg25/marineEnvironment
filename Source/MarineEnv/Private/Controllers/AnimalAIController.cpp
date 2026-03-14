// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AnimalAIController.h"



AAnimalAIController::AAnimalAIController()
{
}

void AAnimalAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn); 
    Animal = Cast<AAnimal>(InPawn);
}


void AAnimalAIController::BeginPlay()
{
    Super::BeginPlay();

}



void AAnimalAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    BehaviourAnalisys();
}
