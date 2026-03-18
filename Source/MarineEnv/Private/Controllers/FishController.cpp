//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Controllers/FishController.h"
#include "Entities/Organism.h"
#include "Kismet/KismetMathLibrary.h"


AFishController::AFishController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}



void AFishController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;


    getModel()->setEnergy(getModel()->getEnergy() - getModel()->getEnergyConsumptionRate() * DeltaTime * getModel()->getSpeed());

    FString CurrentState = getModel()->getCurrentState();

    if (CurrentState == "Idle") {
        if (getModel()->getEnergy() < 90) {
            Target = findFood();
            if (Target) {
                getModel()->setState("Hunting");
                float currentSpeed = getModel()->getSpeed();
                getModel()->setSpeed(currentSpeed * 2);
                getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
                getModel()->setTargetLocation(Target->GetActorLocation());
            }
            else roam(DeltaTime);
        }
        else roam(DeltaTime);
    }
    else if (CurrentState == "Hunting") {
        if (Target){ 
            HuntPrey(DeltaTime);
        }
        else {
            roam(DeltaTime);
        }
    }
    else if (CurrentState == "Fleeing") {

    }
    else if (CurrentState == "Reproduction") {

    }
}

void AFishController::updateMovement(float DeltaTime)
{
    CurrentDirection = FMath::VInterpTo(CurrentDirection, getModel()->getTargetLocation(), DeltaTime, getModel()->getTurnSpeed());


    if (getModel() && getModel()->getDataAsset()) {
        getModel()->AddMovementInput(CurrentDirection, getModel()->getSpeed());
    }

}

void AFishController::roam(float DeltaTime) {

    if (DirectionTimer >= getModel()->getDirectionChangeInterval()) {
        getModel()->setTargetLocation(FMath::VRand());
        DirectionTimer = 0.f;

        if (CurrentDirection.SizeSquared() > KINDA_SMALL_NUMBER)
        {
            FRotator TargetRotation = CurrentDirection.ToOrientationRotator();
            FRotator Smoothed = FMath::RInterpTo(
                getModel()->GetActorRotation(),
                TargetRotation,
                DeltaTime,
                getModel()->getTurnSpeed()
            );
            getModel()->SetActorRotation(Smoothed);
        }
    }
}



void AFishController::HuntPrey(float DeltaTime) {
    if (!Target || !getModel()) {
        if (getModel()) getModel()->setState("Idle");
        return;
    }
   
    if (getModel()->getEnergy() <= 0) {
        getModel()->setEnergy(0);
         
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Hunting"));
        getModel()->setTargetLocation(Target->GetActorLocation());

        updateMovement(DeltaTime);

        float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), getModel()->GetActorLocation());


        if (DistanceToTarget <= 50) {
            getModel()->setEnergy(Target->getEnergy() + getModel()->getEnergy());
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setState("Idle");
            getModel()->setTargetLocation(FMath::VRand());
            Target = nullptr;
        }


        if (DistanceToTarget >= getModel()->getAwarenessRadius()) {
            Target = nullptr;
            getModel()->setState("Idle");
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
        }
    }
}    

AAnimal* AFishController::findMate() {
    // find nearby mates and reproduce
    float radius = 100000.f;


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

AAnimal* AFishController::findFood() {
    float radius = getModel()->getAwarenessRadius();
    int trophicLevel = getModel()->getTrophicLevel();



    TArray<AActor*> FoundActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    TArray<AActor*> ToIgnore;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
    ToIgnore.Add(getModel());

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        getModel()->GetActorLocation(),
        radius,
        ObjectTypes,
        AOrganism::StaticClass(),
        ToIgnore,
        FoundActors
    );


    AAnimal* ClosestFood = nullptr;
    float ClosestDistSq = FLT_MAX;

    for (AActor* Actor : FoundActors)
    {

        AAnimal* Other = Cast<AAnimal>(Actor);
        if (!Other) continue;

        UE_LOG(LogTemp, Warning, TEXT("Vi um animal: %s"), *Other->GetName());

        if (Other->getTrophicLevel() >= trophicLevel) continue;

        FVector direction = getModel()->GetActorLocation() - Other->GetActorLocation();


        float DistSq = FVector::DistSquared(getModel()->GetActorLocation(), Other->GetActorLocation());


        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestFood = Other;
        }
    }


    return ClosestFood;
}