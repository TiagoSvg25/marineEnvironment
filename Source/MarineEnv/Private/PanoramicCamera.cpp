// Fill out your copyright notice in the Description page of Project Settings.

#include "PanoramicCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"


APanoramicCamera::APanoramicCamera()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Root);
    SpringArm->TargetArmLength = 1000.f;                
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    UE_LOG(LogTemp, Warning, TEXT("PanoramicCamera CREATED"));
}

void APanoramicCamera::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeGameAndUI());
        isActive = true;
        if (ControlWidgetClass)
        {
            ControlWidgetInstance = CreateWidget<UControlWidget>(PC, ControlWidgetClass);

            if (ControlWidgetInstance)
            {
                ControlWidgetInstance->AddToViewport();
            }
        }
    }


}


void APanoramicCamera::Zoom(float Value)
{
    if (Value == 0.f) return;

    SpringArm->TargetArmLength = FMath::Clamp(
        SpringArm->TargetArmLength - Value * ZoomSpeed,
        MinZoom,
        MaxZoom
    );
}

void APanoramicCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APanoramicCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    if (PC->WasInputKeyJustPressed(EKeys::H))
    {
        if (ControlWidgetInstance)
        {
            bIsUIVisible = !bIsUIVisible;

            if (bIsUIVisible)
            {
                ControlWidgetInstance->SetVisibility(ESlateVisibility::Visible);
                PC->SetInputMode(FInputModeGameAndUI());
            }
            else
            {
                ControlWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
                PC->SetInputMode(FInputModeGameOnly());
            }
        }
    }


    if (PC->IsInputKeyDown(EKeys::RightMouseButton))
    {
        float MouseX, MouseY;
        PC->GetInputMouseDelta(MouseX, MouseY);

        Yaw += MouseX * OrbitSpeed;
        Pitch = FMath::Clamp(Pitch - MouseY * OrbitSpeed, PitchMin, PitchMax);
        UpdateCamera();
    }

    float Scroll = 0.f;

    if (PC->WasInputKeyJustPressed(EKeys::MouseScrollUp))
    {
        Scroll = 1.f;
    }
    else if (PC->WasInputKeyJustPressed(EKeys::MouseScrollDown))
    {
        Scroll = -1.f;
    }

    if (Scroll != 0.f)
    {
        SpringArm->TargetArmLength = FMath::Clamp(
            SpringArm->TargetArmLength - Scroll * ZoomSpeed,
            MinZoom,
            MaxZoom
        );
    }

}


void APanoramicCamera::ActivateCamera()
{
    isActive = true;
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    PC->bShowMouseCursor = true;
    PC->SetInputMode(FInputModeGameAndUI());
    UpdateCamera();
}

void APanoramicCamera::DeactivateCamera()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    PC->bShowMouseCursor = false;
    PC->SetInputMode(FInputModeGameOnly());
    isActive = false;
}

void APanoramicCamera::UpdateCamera() {
    SpringArm->SetWorldRotation(FRotator(Pitch, Yaw, 0.f));

}