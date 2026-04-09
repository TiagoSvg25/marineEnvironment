//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Controllers/Fish/FishController.h"
#include "Entities/Organism.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <MarineEnv/MarineEnvGameModeBase.h>




AFishController::AFishController()
{
    PrimaryActorTick.bCanEverTick = true;
}




void AFishController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;

    getModel()->setEnergy(getModel()->getEnergy() - getModel()->getEnergyConsumptionRate() * DeltaTime * getModel()->getSpeed());

    FString CurrentState = getModel()->getCurrentState();
    

    if (CurrentState == "Idle") {
        AAnimal* pred = Cast<AAnimal>(find(AAnimal::StaticClass(), {}, false, -1 , getModel()->getTrophicLevel()+1));
        if (pred != nullptr) {
            getModel()->setSpeed(getModel()->getSpeed() * 2);
            getModel()->setTargetLocation(getModel()->GetActorLocation() - pred->GetActorLocation());
            getModel()->setState("Fleeing");
            CurrentFleeTimer = FleeTimer;
        }

        else if (getModel()->getEnergy() < 90) {
            if(getModel()->bIsPredator){
                Target = find(AAnimal::StaticClass(), {}, false, getModel()->getTrophicLevel()-1);
            }
            else {
                Target = find(APlant::StaticClass());
            }
            if (Target) {
                getModel()->setState("Hunting");
                float currentSpeed = getModel()->getSpeed();
                getModel()->setSpeed(currentSpeed * 2);
                getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
                getModel()->setTargetLocation(Target->GetActorLocation());
            }
            else roam(DeltaTime);
        }
        else if (getModel()->getEnergy() > 90) {
            getModel()->setSpeed(getModel()->getSpeed() / 2);
            getModel()->setState("Reproduction");
        }
        else {
            roam(DeltaTime);
        }

    }
    else if (CurrentState == "Hunting") {

        if (Target && getModel()->bIsPredator){
            HuntPrey(DeltaTime);
        }
        else if (!getModel()->bIsPredator) {
            if (Target) {
                UE_LOG(LogTemp, Warning, TEXT("Found plant"));
                getModel()->setTargetLocation(Target->GetActorLocation());
            }
            else {
                Target = find(APlant::StaticClass());
                roam(DeltaTime);
            }
        }
  
    }
    else if (CurrentState == "Fleeing") {
        CurrentFleeTimer -= DeltaTime;
        if(CurrentFleeTimer > 0){
            if (checkPredators() != nullptr) {
                CurrentFleeTimer = FleeTimer;
            }
            FVector NextLoc = FMath::VRand() * 20;
            if (NextLoc.Z < 0) {
                NextLoc.Z = -NextLoc.Z;
            }
            getModel()->setTargetLocation(NextLoc);
        }
        else {
            getModel()->setState("Idle");
            getModel()->setSpeed(getModel()->getSpeed()/2);
        }
    }

    else if (CurrentState == "Reproduction") {
        AAnimal* pred = checkPredators();
        if (pred != nullptr) {
            Target = nullptr;
            getModel()->setSpeed(getModel()->getSpeed() * 2);
            getModel()->setTargetLocation(getModel()->GetActorLocation() - pred->GetActorLocation());
            getModel()->setState("Fleeing");
        }

        if(Target == nullptr){
            Target = find(getModel()->GetClass());
            if (Target && Target->getCurrentState() == "Reproduction") {
                getModel()->setTargetLocation(Target->GetActorLocation());

            }
            else {
                roam(DeltaTime);
            }
        }
        else {
            if (Target->getCurrentState() != "Reproduction") {
                Target = nullptr;
            }
            else{
                getModel()->setTargetLocation(Target->GetActorLocation());
            }
        }
    }
}

void AFishController::Reproduce() {
    
    if(!getModel()) return;

     getModel()->setEnergy(getModel()->getEnergy() * 0.70);

     int spawnAttempts = 10;

     for (int i = 0; i < spawnAttempts; i++) {


        FVector SpawnLocation = getModel()->GetActorLocation() + FMath::VRand()*(getModel()->getMeshAsset()->GetImportedBounds().SphereRadius);
        SpawnLocation.Z = getModel()->GetActorLocation().Z;

        FCollisionShape Sphere = FCollisionShape::MakeSphere(getModel()->getMeshAsset()->GetImportedBounds().SphereRadius);
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(getModel());


        bool bIsOccupied = GetWorld()->OverlapAnyTestByChannel(
            SpawnLocation,
            FQuat::Identity,
            ECC_Pawn,
            Sphere,
            QueryParams
        );

        if (!bIsOccupied)
        {
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

            AFish* NewFish = GetWorld()->SpawnActorDeferred<AFish>(
                getModel()->GetClass(),
                SpawnTransform,
                nullptr,
                nullptr,
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
            );

            if (NewFish)
            {
                NewFish->setState("Idle");
                UGameplayStatics::FinishSpawningActor(NewFish, SpawnTransform);
                UE_LOG(LogTemp, Display, TEXT("New fish successfully created at %s"), *SpawnLocation.ToString());
                return; 
            }
        }


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

    AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

    if (DirectionTimer >= getModel()->getDirectionChangeInterval() || DistToTarget < 10.f) {
        float LocationX = FMath::RandRange(0.f, GameMode->WorldLength);

        float LocationY = FMath::RandRange(0.f, GameMode->WorldWidth);

        FVector Location = FVector(
            LocationX,
            LocationY,
            FMath::RandRange(GetTerrainZ(LocationX, LocationY), GameMode->WorldHeight)
        );

        getModel()->setTargetLocation(Location);
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


        if (DistanceToTarget >= getModel()->getAwarenessRadius()) {
            Target = nullptr;
            getModel()->setState("Idle");
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
        }
    }
}    



void AFishController::onActorCollision(AOrganism* Collided) {

    if (!Target) return;
    if (!getModel()) return; 

    if (getModel()->getCurrentState() == "Hunting") {            
        if (Collided == Target) {
            getModel()->setEnergy(Target->getEnergy() + getModel()->getEnergy());
            getModel()->setSpeed(getModel()->getSpeed()/2);
            getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() / 2);
            getModel()->setState("Idle");
            Target->Destroy();
            Target = nullptr;
        }

    }
    else if (getModel()->getCurrentState() == "Reproduction") {
        if (Collided == Target) {
            Reproduce();
            getModel()->setState("Idle");
            Target->setState("Idle");
            Target = nullptr;
        }

    }

    getModel()->setTargetLocation(getModel()->GetActorLocation() + FMath::VRand() * 10.f);

    return;
}

