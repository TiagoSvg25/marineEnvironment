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
        AAnimal* pred = checkPredators();
        if (pred != nullptr) {
            getModel()->setSpeed(getModel()->getSpeed() * 2);
            getModel()->getTargetLocation() = getModel()->GetActorLocation() - pred->GetActorLocation();
            getModel()->setState("Fleeing");
        }

        else if (getModel()->getEnergy() < 90) {
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
        else {
            roam(DeltaTime);
        }

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




void AFishController::updateMovement(float DeltaTime)
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

void AFishController::roam(float DeltaTime) {
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

void AFishController::HuntPrey(float DeltaTime) {
    if (!Target || !getModel()) {
        if (getModel()) getModel()->setState("Idle");
        return;
    }
   
    if (getModel()->getEnergy() <= 0) {
        getModel()->setEnergy(0);
        getModel()->Destroy();
        // die Animal 
    }


    else {
        getModel()->setTargetLocation(Target->GetActorLocation());

        float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), getModel()->GetActorLocation());


        if (DistanceToTarget <= 50) {
            getModel()->setEnergy(Target->getEnergy() + getModel()->getEnergy());
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setState("Idle");
            getModel()->setTargetLocation(FMath::VRand());
            Target->Destroy();
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
        AFish::StaticClass(),
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
        UE_LOG(LogTemp, Warning, TEXT("Meu nivel: %d, Outro nivel: %d"), trophicLevel, Other->getTrophicLevel());

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