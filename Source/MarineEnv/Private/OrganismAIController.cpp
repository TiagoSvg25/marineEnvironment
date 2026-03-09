// Fill out your copyright notice in the Description page of Project Settings.

#include <Organism.h>
#include <Kismet/GameplayStatics.h>
#include <OrganismAIController.h>

void AOrganismAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Organism) return;

    DetectionTimer += DeltaTime;
    if (DetectionTimer >= Organism->DetectionInterval)
    {
        DetectionTimer = 0.0f;
        updateState();
    }
    Organism->updateMovement(DeltaTime);
}

void AOrganismAIController::updateState() {

	OrganismState currentState = Organism->getState();

	switch (currentState) {
		case OrganismState::Idle:
            if (isHungry) {
                Target = findFood();
                if (Target != NULL) {
                    Organism->setState(OrganismState::Hunting);
                    Organism->CurrentDirection = Target->GetActorLocation();

                    AOrganismAIController* TargetController = Cast<AOrganismAIController>(
                        Target->GetController()
                    );

                    if (TargetController) {
                        TargetController->setPredatorNearby(Organism);
                    }
                }
                
            }
        case OrganismState::Hunting:
        

        case OrganismState::Fleeing:
            
            

	}
	

}

AOrganism* AOrganismAIController::findFood() {
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

        // only target lower trophic levels
        if (Other->getEnvironmentalCharacteristics().TrophicLevel >= trophicLevel) continue;

        float DistSq = FVector::DistSquared(Other->GetActorLocation(), Organism->GetActorLocation());
        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestFood = Other;
        }
    }

    return ClosestFood;
}

void AOrganismAIController::setPredatorNearby(AOrganism* InPredator)
{
    Predator = InPredator;
    if (Organism)
        Organism->setState(OrganismState::Fleeing);
}


