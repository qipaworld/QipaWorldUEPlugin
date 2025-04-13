// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#include "Widget/QPColorWidget.h"

/// Slate Overrides ///

TSharedRef<SWidget> UQPColorWidget::RebuildWidget()
{
    ColorWheel = SNew(QPSWColorWheel)
                .SelectedColor_UObject(this, &UQPColorWidget::GetHSVColor)
                .SelectorPin(&SelectorPin)
                .HueCircle(&HueCircle)
                .OnMouseCaptureBegin_UObject(this, &UQPColorWidget::MouseDown)
                .OnMouseCaptureEnd_UObject(this, &UQPColorWidget::MouseUp)
                .OnValueChanged(FOnLinearColorValueChanged::CreateUObject(this, &UQPColorWidget::OnValueChanged))
                .OnPositionChanged(FOnPositionChanged::CreateUObject(this, &UQPColorWidget::OnPositionUpdated));
	
    return ColorWheel.ToSharedRef();
}

void UQPColorWidget::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    ColorWheel.Reset();
}

void UQPColorWidget::OnValueChanged(FLinearColor NewValue)
{
    Color = NewValue.HSVToLinearRGB();
    OnColorChanged.Broadcast(Color);
}


void UQPColorWidget::OnPositionUpdated(FVector2D NewPosition)
{
    //UE_LOG(LogTemp, Warning, TEXT("D - X: %f - Y: %f"), NewPosition.X, NewPosition.Y)
    OnPositionChanged.Broadcast(NewPosition);
}

/// Main Functions ///

void UQPColorWidget::SetColor(const FLinearColor NewColor)
{
    // Incase of Black, the wheel gets fucked ヽ(`Д´)ﾉ︵ ┻━┻.
    if (NewColor.IsAlmostBlack())
    {
        // We pass in a false value
        Color = FLinearColor::White;
        
        // Preserve alpha.
        Color.A = NewColor.A;
        IsNull = true;
        
        return;
    }

    Color = NewColor;
    IsNull = false;
}

FLinearColor UQPColorWidget::GetCurrentColor()
{
    // Was input black?
    if (IsNull)
    {
        // Return black color
        auto FallbackVal = FLinearColor::Black;
        FallbackVal.A = Color.A;
        
        return FallbackVal;
    }

    return Color;
}

/// Generics ///

void UQPColorWidget::SetColorAndOpacity(FLinearColor InColorAndOpacity, TEnumAsByte<EWheelBrushTarget> Target)
{
    // Update the values themselves, again this doesnt look good so change it later perhaps.
    auto ColorVal = FSlateColor(InColorAndOpacity);
    switch (Target)
    {
        case EWheelBrushTarget::All:
            SelectorPin.TintColor = ColorVal;
            HueCircle.TintColor = ColorVal;
            break;

        case EWheelBrushTarget::SelectorPin:
            SelectorPin.TintColor = ColorVal;
            break;

        case EWheelBrushTarget::HueCircle:
            HueCircle.TintColor = ColorVal;
            break;
    }

    // Update the visual widget itself
    if (ColorWheel.IsValid())
    {
        ColorWheel->SetColorAndOpacity(InColorAndOpacity, Target);
    }
}



