#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "ControlWidget.generated.h"

UCLASS()
class MARINEENV_API UControlWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    USlider* FogSlider;

    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnSliderValueChanged(float Value);

    UPROPERTY(meta = (BindWidget))
    class USlider* SpeedSlider;

    UFUNCTION()
    void OnSpeedValueChanged(float Value);
};