#include "Controllers/Fish/FlockingController.h"
#include <MarineEnv/MarineEnvGameModeBase.h>
#include "Kismet/GameplayStatics.h"

AFlockingController::AFlockingController() {}

void AFlockingController::BehaviourAnalisys(float DeltaTime)
{
    if (!getModel()) return;

    FString CurrentState = getModel()->getCurrentState();


    if (getModel()->getEnergy() <= 0) {
        getModel()->Destroy();
        return;
    }

    if (CurrentState == "Idle") {

        TArray<AActor*> allActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFish::StaticClass(), allActors);

        AFish* nearbyFish = nullptr;
        for (AActor* actor : allActors) {
            AFish* other = Cast<AFish>(actor);
            if (!other || other == getModel()) continue;

            bool sameTags = true;
            for (auto& tag : getModel()->getTags()) {
                bool found = false;
                for (auto& otherTag : other->getTags()) {
                    if (tag.Equals(otherTag, ESearchCase::IgnoreCase)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    sameTags = false;
                    break;
                }
            }
            if (!sameTags) continue;

            float dist = FVector::Dist(getModel()->GetActorLocation(), other->GetActorLocation());
            if (dist <= getModel()->getAwarenessRadius()) {
                nearbyFish = other;
                break;
            }
        }

        if (nearbyFish != nullptr) {
            getModel()->setState("Flocking");
            getModel()->setSpeed(getModel()->getBaseSpeed());
            getModel()->getShoalSubsystem()->AddShoal(getModel());
            return;
        }

        Super::BehaviourAnalisys(DeltaTime);
        return;
    }

    if (CurrentState == "Flocking") {

        AAnimal* pred = Cast<AAnimal>(find(AAnimal::StaticClass(), {}, false, -1, getModel()->getTrophicLevel() + 1));
       
        if (pred != nullptr) {
            
            getModel()->setState("Fleeing");
            getModel()->setSpeed(getModel()->getSpeed() * 2);

            FVector FleeDir = (getModel()->GetActorLocation() - pred->GetActorLocation()).GetSafeNormal();
            getModel()->setTargetLocation(getModel()->GetActorLocation() + (FleeDir * 1000.f));

            CurrentFleeTimer = FleeTimer;
            alertShoalDanger();

            getModel()->getShoalSubsystem()->RemoveShoal(Cast<AFish>(getModel()), getModel()->getShoalId());
            getModel()->setShoalId("");
            getModel()->setNeighbors(TArray<AFish*>());
            
           
            Super::BehaviourAnalisys(DeltaTime);
            return;
        }

        else if (getModel()->getEnergy() < getModel()->getEnergyThreshold()) {

            if (getModel()->bIsPredator) {
                Target = find(AAnimal::StaticClass(), {}, false, getModel()->getTrophicLevel() - 1);
            }
            else {
                Target = find(APlant::StaticClass());
            }

            if (Target) {
                int huntChance = FMath::RandRange(0, 1000);

                if (huntChance < 10) {
                    getModel()->setState("Hunting");
                    float currentSpeed = getModel()->getSpeed();
                    getModel()->setSpeed(currentSpeed * 2);
                    getModel()->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);
                    getModel()->setTargetLocation(Target->GetActorLocation());
                    getModel()->setTurnSpeed(getModel()->getTurnSpeed() * 2);

                    getModel()->getShoalSubsystem()->RemoveShoal(Cast<AFish>(getModel()), getModel()->getShoalId());
                    getModel()->setShoalId("");
                    getModel()->setNeighbors(TArray<AFish*>());

                    Super::BehaviourAnalisys(DeltaTime);
                    return;
                }
            }
        }

        TArray<AFish*> currentNeighbors;
        TArray<AActor*> allActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFish::StaticClass(), allActors);

        for (AActor* actor : allActors) {
            AFish* other = Cast<AFish>(actor);
            if (!other || other == getModel()) continue;

            bool sameTags = true;
            for (auto& tag : getModel()->getTags()) {
                bool found = false;
                for (auto& otherTag : other->getTags()) {
                    if (tag.Equals(otherTag, ESearchCase::IgnoreCase)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    sameTags = false;
                    break;
                }
            }
            if (!sameTags) continue;

            float dist = FVector::Dist(getModel()->GetActorLocation(), other->GetActorLocation());
            if (dist <= getModel()->getAwarenessRadius()) {
                currentNeighbors.Add(other);
            }
        }

        getModel()->setNeighbors(currentNeighbors);

        if (currentNeighbors.Num() == 0) {
            getModel()->getShoalSubsystem()->RemoveShoal(Cast<AFish>(getModel()), getModel()->getShoalId());
            getModel()->setShoalId("");
            getModel()->setState("Idle");
            return;
        }

        flockingBehaviour();

        Super::BehaviourAnalisys(DeltaTime);
        return;
    }

    Super::BehaviourAnalisys(DeltaTime);
}

void AFlockingController::alertShoalDanger() {
    for (AFish* neighbor : getModel()->getNeighbors()) {

        if (neighbor && neighbor->getCurrentState() == "Flocking")
        {
            AAnimalAIController* NeighborController = Cast<AAnimalAIController>(neighbor->GetController());

            if (NeighborController) {
                NeighborController->resetFleeTimer();
            }

            neighbor->setState("Fleeing");

            FVector DirectionAway = (neighbor->GetActorLocation() - getModel()->GetActorLocation()).GetSafeNormal();
            neighbor->setTargetLocation(neighbor->GetActorLocation() + (DirectionAway * 1000.f));
            neighbor->setEnergyConsumptionRate(getModel()->getEnergyConsumptionRate() * 2);


            neighbor->getShoalSubsystem()->RemoveShoal(neighbor, neighbor->getShoalId());
            neighbor->setShoalId("");
            neighbor->setNeighbors(TArray<AFish*>());
        }
    }
}



void AFlockingController::flockingBehaviour()
{
    if (getModel()->getNeighbors().Num() == 0) return;

    alignWithNeighbors();
    cohesionWithNeighbors();
    separateFromNeighbors();

    FVector CenterOfMass = FVector::ZeroVector;


    for (AFish* neighbor : getModel()->getNeighbors()) {
        CenterOfMass += neighbor->GetActorLocation();
    }
    CenterOfMass /= getModel()->getNeighbors().Num();

    float distToCenter = FVector::Dist(getModel()->GetActorLocation(), CenterOfMass);
    float cohesionFactor = FMath::Clamp(distToCenter / 300.0f, 0.5f, 2.0f);

    bool bTooClose = false;
    for (AFish* neighbor : getModel()->getNeighbors()) {
        float dist = FVector::Dist(getModel()->GetActorLocation(), neighbor->GetActorLocation());
        if (dist < SeparationDistance * 0.5f) {
            bTooClose = true;
            break;
        }
    }

    float CurrentSeparationWeight = SeparationWeight;
    float CurrentAlignWeight = AlignWeight;
    float CurrentCohesionWeight = CohesionWeight * cohesionFactor;

    if (bTooClose) {
        CurrentSeparationWeight *= 4.0f;
        CurrentAlignWeight *= 0.5f;
        CurrentCohesionWeight *= 0.1f;
    }
    
    FVector FlockingForce =
        AlignmentVector.GetSafeNormal() * CurrentAlignWeight +
        CohesionVector.GetSafeNormal() * CurrentCohesionWeight +
        SeparationVector.GetSafeNormal() * CurrentSeparationWeight;


    AMarineEnvGameModeBase* GameMode = Cast<AMarineEnvGameModeBase>(GetWorld()->GetAuthGameMode());

    float targetDistance = FMath::Max(getModel()->getAwarenessRadius() * 0.5f, 300.0f);
    FVector NewTarget = getModel()->GetActorLocation() + FlockingForce.GetSafeNormal() * targetDistance;

    if (GameMode) {

        float MinX = -GameMode->WorldLength / 2.0f + 200.f;
        float MaxX = GameMode->WorldLength / 2.0f - 200.f;

        float MinY = -GameMode->WorldWidth / 2.0f + 200.f;
        float MaxY = GameMode->WorldWidth / 2.0f - 200.f;

        NewTarget.X = FMath::Clamp(NewTarget.X, MinX, MaxX);
        NewTarget.Y = FMath::Clamp(NewTarget.Y, MinY, MaxY);

        float TerrainZ = GetTerrainZ(NewTarget.X, NewTarget.Y); 
        float SafeMinZ = TerrainZ + 100.f;                     
        float SafeMaxZ = GameMode->WorldHeight - 100.f;        

        NewTarget.Z = FMath::Clamp(NewTarget.Z, SafeMinZ, SafeMaxZ);
    }

    getModel()->setTargetLocation(NewTarget);


    float baseSpeed = getModel()->getBaseSpeed();

    float avgSpeed = 0.f;
    for (AFish* neighbor : getModel()->getNeighbors()) {
        avgSpeed += neighbor->getSpeed();
    }
    avgSpeed /= getModel()->getNeighbors().Num();
    avgSpeed = FMath::Clamp(avgSpeed, baseSpeed * 0.5f, baseSpeed * 1.2f);

    float targetSpeed = bTooClose ? baseSpeed * 1.2f : avgSpeed;

    float newSpeed = FMath::FInterpTo(
        getModel()->getSpeed(),
        targetSpeed,
        GetWorld()->GetDeltaSeconds(),
        2.0f
    );
    getModel()->setSpeed(newSpeed);
}




void AFlockingController::alignWithNeighbors()
{
    FVector AverageDirection = FVector::ZeroVector;
    for (AFish* neighbor : getModel()->getNeighbors()) {
        AverageDirection += neighbor->GetActorForwardVector();
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
    FVector Separation = FVector::ZeroVector;
    int count = 0;

    for (AFish* neighbor : getModel()->getNeighbors()) {
        float dist = FVector::Dist(getModel()->GetActorLocation(), neighbor->GetActorLocation());

        if (dist < SeparationDistance && dist > 0.f) {

            float weight = 1.0f - (dist / SeparationDistance);
            Separation += (getModel()->GetActorLocation() - neighbor->GetActorLocation()).GetSafeNormal() * weight;
            count++;
        }
    }

    SeparationVector = (count > 0) ? Separation / count : FVector::ZeroVector;
}