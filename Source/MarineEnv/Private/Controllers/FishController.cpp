//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Controllers/FishController.h"
#include "Entities/Organism.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"




AFishController::AFishController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}




void AFishController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;

    UE_LOG(LogTemp, Warning, TEXT("Energy: %f"), getModel()->getEnergy());
    UE_LOG(LogTemp, Warning, TEXT("State: %s"), *getModel()->getCurrentState());
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
                Target = Cast<AAnimal>(find(AAnimal::StaticClass(), {}, false, getModel()->getTrophicLevel()-1));
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
                AOrganism* Plant = find(AOrganism::StaticClass(), {"plant"}, true);
                if (Plant) {
                    getModel()->setState("Hunting");
                    float currentSpeed = getModel()->getSpeed();
                    getModel()->setSpeed(currentSpeed * 2);
                    getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
                    getModel()->setTargetLocation(Plant->GetActorLocation());
                }
                else roam(DeltaTime);
            }
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

        if (Target){ 
            HuntPrey(DeltaTime);
        }
        else if (!getModel()->bIsPredator) {
            AOrganism* Plant = find(AOrganism::StaticClass(), { "plant" }, true);
            if (Plant) {
                getModel()->setTargetLocation(Plant->GetActorLocation());
            }
            else {
                roam(DeltaTime);
            }
        }
        else {
            roam(DeltaTime);
        }
    }
    else if (CurrentState == "Fleeing") {
        CurrentFleeTimer -= DeltaTime;
        if(CurrentFleeTimer > 0){
            if (checkPredators() != nullptr) {
                CurrentFleeTimer = FleeTimer;
            }
            FVector NextLoc = FMath::VRand() * 100;
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
            Target = Cast<AAnimal>(find(getModel()->GetClass()));
            if (Target && Target->getCurrentState() == "Reproduction") {
                getModel()->setTargetLocation(Target->GetActorLocation());
            }
            else {
                roam(DeltaTime);
            }
        }
        else {
            getModel()->setTargetLocation(Target->GetActorLocation());
            if(FVector::Dist(getModel()->GetActorLocation(), Target->GetActorLocation()) < 50.f){
                Reproduce();
                getModel()->setState("Idle");
                Target->setState("Idle");
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

    if (DirectionTimer >= getModel()->getDirectionChangeInterval() || DistToTarget < 10.f) {
        FVector RandomOffset = FMath::VRand()*300.f;
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