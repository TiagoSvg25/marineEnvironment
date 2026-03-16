//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Controllers/FishController.h"
#include "Entities/Organism.h"


AFishController::AFishController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}



void AFishController::BehaviourAnalisys(float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("Current State:~antes"));
    if (!getModel()) return;


    getModel()->setEnergy(getModel()->getEnergy() - getModel()->getEnergyConsumptionRate() * DeltaTime * getModel()->getSpeed());

    FString CurrentState = getModel()->getCurrentState();
    UE_LOG(LogTemp, Warning, TEXT("Current State: %s"), *CurrentState);

    if (CurrentState == "Idle") {
        updateMovement(DeltaTime, FVector(1000, 1000, 2));
    }
    else if (CurrentState == "Hunting") {
        //f (Target) HuntPrey();
    }
    else if (CurrentState == "Fleeing") {

    }
    else if (CurrentState == "Reproduction") {

    }
}


/*
void AFishController::HuntPrey() {
   
    // if it starts hunting, increase speed by 2x
    if (getModel()->isHunting()) {
        getModel()->setHunting(true);
        float currentSpeed = getModel()->getSpeed();
        getModel()->setSpeed(currentSpeed * 2);
        getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
    }






    if (getModel()->getEnergy() <= 0) {
        getModel()->setEnergy(0);
        // die Animal 
    }

    /* if it stops hunting, reset speed to normal
    if (Target->GetActorLocation() == getModel()->getAwarenessRadius()) {
        getModel()->setHunting(false);
        float currentSpeed = getModel()->getSpeed();
        getModel()->setSpeed(currentSpeed / 2);
        getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
        getModel()->setState("Idle");
    }
}    */

void AFishController::updateMovement(float DeltaTime, FVector TargetLocation)
{
    if (getModel() && getModel()->getDataAsset()) {
        getModel()->AddMovementInput(getModel()->GetActorForwardVector(), getModel()->getSpeed());
    }
}




/*
void AFishController::updateState() {
    //
}

AOrganism* AFishController::findFood() {
    AOrganism* ClosestFood = nullptr;
    return ClosestFood;
}

*/















/*void AFishController::updateState() {

    OrganismState currentState = Organism->getState();
    switch (currentState) {
    case OrganismState::Idle:
        if (isHungry) {
            Target = findFood();
            if (Target != nullptr) {
                Organism->setState(OrganismState::Hunting);

                AOrganismAIController* TargetController = Cast<AOrganismAIController>(
                    Target->GetController()
                );

                if (TargetController) {
                    TargetController->setPredatorNearby(Organism);
                }
                break;
            }
        }
        else {
            float rand = FMath::RandRange(0, 1);
            if (rand > 0.90) {
                isHungry = true;
            }
            if (DirectionTimer >= Organism->DirectionChangeInterval) {
                Organism->calculateVectors();
                DirectionTimer = 0.f;
            }
        }

        break;

    case OrganismState::Hunting:
        if (Target) {
            Organism->TargetDirection = (Target->GetActorLocation() - Organism->GetActorLocation()).GetSafeNormal();

            if (checkEscape(Target, Organism)) {
                Organism->setState(OrganismState::Idle);
                UE_LOG(LogTemp, Warning, TEXT("Prey Escaped:"));

            }

        }
        break;

    case OrganismState::Fleeing:
        if (Predator) {
            if (checkEscape(Organism, Predator)) {
                UE_LOG(LogTemp, Warning, TEXT("Escaped:"));
                Organism->setState(OrganismState::Idle);
            }
            else {
                FVector FleeDirection = Organism->GetActorLocation() - Predator->GetActorLocation();
                FVector RandomOffset = FMath::VRand() * 0.8f;
                Organism->TargetDirection = (FleeDirection.GetSafeNormal() + RandomOffset).GetSafeNormal();
            }
        }
        break;
    default:
        break;
    }
}

AOrganism* AFishController::findFood() {
    float radius = Organism->getMovementCharacteristics().AwarenessRadius;
    int trophicLevel = Organism->getEnvironmentalCharacteristics().TrophicLevel;



    TArray<AActor*> FoundActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    TArray<AActor*> ToIgnore;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
    ToIgnore.Add(Organism);

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        Organism->GetActorLocation(),
        radius,
        ObjectTypes,
        AOrganism::StaticClass(),
        ToIgnore,
        FoundActors
    );


    AOrganism* ClosestFood = nullptr;
    float ClosestDistSq = FLT_MAX;

    for (AActor* Actor : FoundActors)
    {
        AOrganism* Other = Cast<AOrganism>(Actor);
        if (!Other) continue;

        if (Other->getEnvironmentalCharacteristics().TrophicLevel >= trophicLevel) continue;

        FVector direction = Organism->GetActorLocation() - Other->GetActorLocation();


        float DistSq = FVector::DistSquared(Organism->GetActorLocation(), Other->GetActorLocation());


        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestFood = Other;
        }
    }


    return ClosestFood;
}



*/