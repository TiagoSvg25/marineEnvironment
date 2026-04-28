// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PanoramicCamera.generated.h"

UCLASS()
class MARINEENV_API APanoramicCamera : public APawn
{
    GENERATED_BODY()

public:
    APanoramicCamera();
    
    UFUNCTION(BlueprintCallable)
    void ActivateCamera();

    UFUNCTION(BlueprintCallable)
    void DeactivateCamera(); 
    
    UPROPERTY(BlueprintReadWrite, Category = "Input")
    float ScrollValue = 0.f;


    UPROPERTY(BlueprintReadWrite, Category = "Active")
    bool isActive = false;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    float Yaw = 0.f;
    float Pitch = -30.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float OrbitSpeed = 0.5f;


    UPROPERTY(EditAnywhere, Category = "Orbit")
    float ZoomSpeed = 500.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float MinZoom = 200.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float MaxZoom = 20000.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float PitchMin = -80.f;

    UPROPERTY(EditAnywhere, Category = "Orbit")
    float PitchMax = 10.f;

    void UpdateCamera();

    void Zoom(float Value);

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


};