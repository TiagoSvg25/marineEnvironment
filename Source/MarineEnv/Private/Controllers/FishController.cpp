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
        if (getModel()->getEnergy() < 80) getModel()->setState("Hunting");

        else {
            updateMovement(DeltaTime);
        }
    }
    else if (CurrentState == "Hunting") {
        findFood();
        if (Target) HuntPrey(DeltaTime);
    }
    else if (CurrentState == "Fleeing") {

    }
    else if (CurrentState == "Reproduction") {
        findMate();
    }
}



void AFishController::HuntPrey(float DeltaTime) {
    if (getModel()->getEnergy() <= 0) {
        getModel()->setEnergy(0);
        // die Animal 
    }


    // if it starts hunting, increase speed by 2x
    if (!getModel()->isHunting()) {
        getModel()->setHunting(true);
        float currentSpeed = getModel()->getSpeed();
        getModel()->setSpeed(currentSpeed * 2);
        getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);

        TargetLocation = Target->GetActorLocation();

        updateMovement(DeltaTime);

    }
    else {
        TargetLocation = Target->GetActorLocation();

        updateMovement(DeltaTime);

        float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), getModel()->GetActorLocation());


        if (DistanceToTarget <= 2) {
            // eat the prey
            getModel()->setEnergy(Target->getEnergy() + getModel()->getEnergy());
            getModel()->setSpeed(getModel()->getSpeed() / 2);
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setState("Idle");
            TargetLocation = FMath::VRand();
        }


        if (DistanceToTarget >= getModel()->getAwarenessRadius()) {
            getModel()->setHunting(false);
            float currentSpeed = getModel()->getSpeed();
            getModel()->setSpeed(currentSpeed / 2);
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setHunting(false);
        }
    }
}    


void AFishController::updateMovement(float DeltaTime)
{
    CurrentDirection = FMath::VInterpTo(CurrentDirection, TargetLocation, DeltaTime, getModel()->getDirectionChangeInterval());


    if (getModel() && getModel()->getDataAsset()) {
        getModel()->AddMovementInput(CurrentDirection, getModel()->getSpeed());
    }


    if (DirectionTimer >= getModel()->getDirectionChangeInterval()) {

        TargetLocation = FMath::VRand();
        DirectionTimer = 0.f;

        if (CurrentDirection.SizeSquared() > KINDA_SMALL_NUMBER)
        {
            FRotator TargetRotation = CurrentDirection.ToOrientationRotator();
            FRotator Smoothed = FMath::RInterpTo(
                getModel()->GetActorRotation(),
                TargetRotation,
                DeltaTime,
                getModel()->getDirectionChangeInterval()
            );
            getModel()->SetActorRotation(Smoothed);
        }
    }
}



AAnimal* AFishController::findMate() {
    // find nearby mates and reproduce
    float radius = getModel()->getAngleVision();


    TArray<AActor*> FoundActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    TArray<AActor*> ToIgnore;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
    ToIgnore.Add(this);

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        getModel()->GetActorLocation(),
        radius,
        ObjectTypes,
        AAnimal::StaticClass(),
        ToIgnore,
        FoundActors
    );



    AAnimal* ClosestMate = nullptr;
    float ClosestDistSq = getModel()->getAwarenessRadius();

    for (AActor* Actor : FoundActors)
    {
        AAnimal* Other = Cast<AAnimal>(Actor);
        if (!Other) continue;


        FVector direction = getModel()->GetActorLocation() - Other->GetActorLocation();


        float DistSq = FVector::DistSquared(getModel()->GetActorLocation(), Other->GetActorLocation());


        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestMate = Other;
        }
    }

    return ClosestMate;

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