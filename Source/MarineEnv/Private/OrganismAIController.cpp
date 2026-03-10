// Fill out your copyright notice in the Description page of Project Settings.

#include <Organism.h>
#include <Kismet/GameplayStatics.h>
#include <OrganismAIController.h>

AOrganismAIController::AOrganismAIController()
{
    PrimaryActorTick.bCanEverTick = true; // must be true
}

void AOrganismAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    Organism = Cast<AOrganism>(InPawn);

    UE_LOG(LogTemp, Warning, TEXT("Controller possessed:"));

}


void AOrganismAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (!Organism) return;

    DirectionTimer += DeltaTime;
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
                UE_LOG(LogTemp, Warning, TEXT("Finding Food:"));
                Target = findFood();
                if (Target != nullptr) {
                    UE_LOG(LogTemp, Warning, TEXT("Found Food:"));
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
            else{
                float rand = FMath::RandRange(0, 1);
                if (rand > 0.90) {
                    UE_LOG(LogTemp, Warning, TEXT("Got Hungry:"));
                    isHungry = true;
                }
                if (DirectionTimer >= Organism->DirectionChangeInterval) {
                    Organism->calculateVectors();
                    DirectionTimer = 0.f;
                }
            }

            break;

        case OrganismState::Hunting:
            UE_LOG(LogTemp, Warning, TEXT("Hunting:"));
            if(Target){
                Organism->TargetDirection = (Target->GetActorLocation() - Organism->GetActorLocation()).GetSafeNormal();

                if (checkEscape(Target,Organism)) {
                    Organism->setState(OrganismState::Idle);
                    UE_LOG(LogTemp, Warning, TEXT("Prey Escaped:"));

                }

            }
            break;

        case OrganismState::Fleeing:
            UE_LOG(LogTemp, Warning, TEXT("Fleeing:"));
            if(Predator){
                if (checkEscape(Organism, Predator)) {
                    UE_LOG(LogTemp, Warning, TEXT("Escaped:"));
                    Organism->setState(OrganismState::Idle);
                }
                else {
                    FVector FleeDirection = Organism->GetActorLocation() - Predator->GetActorLocation();
                    FVector RandomOffset = FMath::VRand() * 0.6f;
                    Organism->TargetDirection = (FleeDirection.GetSafeNormal() + RandomOffset).GetSafeNormal();
                }
            }
            break;
        default:
            break;
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
    UE_LOG(LogTemp, Warning, TEXT("Actors found in radius: %d"), FoundActors.Num());



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

void AOrganismAIController::setPredatorNearby(AOrganism* InPredator)
{
    Predator = InPredator;
    if (Organism)
        Organism->setState(OrganismState::Fleeing);
}

bool AOrganismAIController::checkEscape(AOrganism* Prey, AOrganism* InPredator) {

    if(!InPredator || !Prey) return true;
        
    float distance = FVector::DistSquared(Prey->GetActorLocation(), InPredator->GetActorLocation());
    UE_LOG(LogTemp, Warning, TEXT("Distance: %f, AWare: %f"), FMath::Sqrt(distance), InPredator->getMovementCharacteristics().AwarenessRadius);
    return FMath::Sqrt(distance) > InPredator->getMovementCharacteristics().AwarenessRadius;
}



void AOrganismAIController::onCatchPrey(AOrganism* Collided) {

    if(!Target) return;
    if(Collided != Target) return;

    isHungry = false;
    Organism->setState(OrganismState::Idle);
    Collided->Destroy();
    Target = nullptr;
    UE_LOG(LogTemp, Warning, TEXT("Caught prey!"));

    return;
}

void AOrganismAIController::onTerrainCollision(FVector Normal) {
    if (!Organism) return;

    FVector newDir = FMath::GetReflectionVector(Organism->CurrentDirection,Normal);

    Organism->TargetDirection = newDir.GetSafeNormal();
}


