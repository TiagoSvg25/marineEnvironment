// Fill out your copyright notice in the Description page of Project Settings.


#include "Sardine.h"

ASardine::ASardine()
{

}

void ASardine::BeginPlay()
{
	Super::BeginPlay();

	setTrophicLevel(1);

	setSpeed(1.0f);

	setEnergyThreshold(50.0f);

	setEnergyConsumptionRate(0.4f);

	setAwarenessRadius(1000.0f);

	setAngleVision(60.0f);

	setTurnSpeed(1.0f);

	setDirectionChangeInterval(2.0f);

	addTag("Sardine");
	addTag("Schooling");
}

void ASardine::Tick(float DeltaTime)
{
}
