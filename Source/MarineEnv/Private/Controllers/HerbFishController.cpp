//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Controllers/HerbFishController.h"
#include "Entities/Organism.h"
#include "Entities/Plant.h"
#include "Kismet/KismetMathLibrary.h"


AHerbFishController::AHerbFishController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}



void AHerbFishController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;


    getModel()->setEnergy(getModel()->getEnergy() - getModel()->getEnergyConsumptionRate() * DeltaTime * getModel()->getSpeed());

    FString CurrentState = getModel()->getCurrentState();

    if (CurrentState == "Idle") {
        AAnimal* pred = checkPredators();
        if (pred != nullptr) {
            getModel()->setSpeed(getModel()->getSpeed() * 2);
            getModel()->getTargetLocation() = getModel()->GetActorLocation() - pred->GetActorLocation();
            getModel()->setState("Fleeing");
        }

        else if (getModel()->getEnergy() < 90) {
            getModel()->setTargetHerb(findPlant());
            auto HTarget = getModel()->getTargetHerb();
            if (HTarget) {
                getModel()->setState("Hunting");
                float currentSpeed = getModel()->getSpeed();
                getModel()->setSpeed(currentSpeed * 2);
                getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
                getModel()->setTargetLocation(HTarget->GetActorLocation());
            }
            else roam(DeltaTime);
        }
        else {
            roam(DeltaTime);
        }
    }
    else if (CurrentState == "Hunting") {
        auto HTarget = getModel()->getTargetHerb();
        if (HTarget) {
            HuntPrey(DeltaTime);
        }
        else {
            roam(DeltaTime);
        }
    }
    else if (CurrentState == "Fleeing") {
        if (getModel()->getEnergy() >= 0.30 * getModel()->getMaxEnergy()) {

            getModel()->setTargetLocation(FMath::VRand().GetSafeNormal());
        }
        else {
            if (checkPredators() != nullptr) {
                getModel()->setTargetLocation(FMath::VRand().GetSafeNormal());
            }
            else {
                getModel()->setSpeed(getModel()->getSpeed() / 2);
                getModel()->setState("Idle");
            }
        }



    }
    else if (CurrentState == "Reproduction") {

    }
}

void AHerbFishController::updateMovement(float DeltaTime)
{
    FVector CurrentLocation = getModel()->GetActorLocation();
    FVector TargetLocation = getModel()->getTargetLocation();

    FVector DesiredDirection = (TargetLocation - CurrentLocation).GetSafeNormal();

    CurrentDirection = FMath::VInterpTo(CurrentDirection, DesiredDirection, DeltaTime, getModel()->getTurnSpeed());
    CurrentDirection = CurrentDirection.GetSafeNormal();

    getModel()->AddMovementInput(CurrentDirection, getModel()->getSpeed());

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

void AHerbFishController::roam(float DeltaTime) {
    FVector CurrentLocation = getModel()->GetActorLocation();
    float DistToTarget = FVector::Dist(CurrentLocation, getModel()->getTargetLocation());

    if (DirectionTimer >= getModel()->getDirectionChangeInterval() || DistToTarget < 10.f) {
        FVector RandomOffset = FMath::VRand() * 300.f;
        FVector NewTarget = CurrentLocation + RandomOffset;
        if (NewTarget.Z <= 0) {
            NewTarget.Z = 0 - NewTarget.Z;
        }
        getModel()->setTargetLocation(NewTarget);
        DirectionTimer = 0.f;
    }
}

void AHerbFishController::HuntPrey(float DeltaTime) {
    auto HTarget = getModel()->getTargetHerb();
    if (!HTarget || !getModel()) {
        if (getModel()) getModel()->setState("Idle");
        return;
    }

    if (getModel()->getEnergy() <= 0) {
        getModel()->setEnergy(0);
        getModel()->Destroy();
        // die Animal 
    }


    else {
        getModel()->setTargetLocation(HTarget->GetActorLocation());

        float DistanceToTarget = FVector::Dist(HTarget->GetActorLocation(), getModel()->GetActorLocation());


        if (DistanceToTarget <= 50) {
            getModel()->setEnergy(HTarget->getEnergy() + getModel()->getEnergy());
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setState("Idle");
            getModel()->setTargetLocation(FMath::VRand());
            HTarget->Destroy();
            HTarget = nullptr;
        }


        if (DistanceToTarget >= getModel()->getAwarenessRadius()) {
            HTarget = nullptr;
            getModel()->setState("Idle");
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
        }
    }
}

AAnimal* AHerbFishController::findMate() {
    // find nearby mates and reproduce
    float radius = getModel()->getAwarenessRadius();


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



APlant* AHerbFishController::findPlant() {
    float radius = getModel()->getAwarenessRadius();



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
        APlant::StaticClass(),
        ToIgnore,
        FoundActors
    );

    APlant* ClosestFood = nullptr;
    float ClosestDistSq = FLT_MAX;

    for (AActor* Actor : FoundActors)
    {

        APlant* Other = Cast<APlant>(Actor);
        if (!Other) continue;
        UE_LOG(LogTemp, Warning, TEXT("Vi uma planta: %s"), *Other->GetName());
        //UE_LOG(LogTemp, Warning, TEXT("Meu nivel: %d, Outro nivel: %d"), trophicLevel, Other->getTrophicLevel());

        //if (Other->getTrophicLevel() >= trophicLevel) continue;

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