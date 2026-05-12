#include "ControlWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Engine/ExponentialHeightFog.h"

void UControlWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (FogSlider)
    {
        FogSlider->OnValueChanged.AddDynamic(this, &UControlWidget::OnSliderValueChanged);

        FogSlider->SetMinValue(0.0f);
        FogSlider->SetMaxValue(1.0f);

        AActor* FogActor = UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass());
        if (AExponentialHeightFog* Fog = Cast<AExponentialHeightFog>(FogActor))
        {
            if (UExponentialHeightFogComponent* FogComp = Fog->GetComponent()){
            
                FogSlider->SetValue(FogComp->FogDensity);
            }
        }
    }
    if (SpeedSlider)
    {
        SpeedSlider->OnValueChanged.AddDynamic(this, &UControlWidget::OnSpeedValueChanged);
        SpeedSlider->SetMinValue(0.0f);
        SpeedSlider->SetMaxValue(4.0f);
        SpeedSlider->SetValue(1.0f);
    }
    
}

void UControlWidget::OnSliderValueChanged(float Value)
{
    AActor* FogActor = UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass());

    if (AExponentialHeightFog* Fog = Cast<AExponentialHeightFog>(FogActor))
    {
        if (UExponentialHeightFogComponent* FogComp = Fog->GetComponent())
        {
            FogComp->FogDensity = Value;

            FogComp->MarkRenderStateDirty();
        }
    }
}

void UControlWidget::OnSpeedValueChanged(float Value)
{
    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), Value);
}