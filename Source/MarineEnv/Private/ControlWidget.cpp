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