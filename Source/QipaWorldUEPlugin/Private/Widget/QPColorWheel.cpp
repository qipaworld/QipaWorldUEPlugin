/*
	By Rama for You
	
	You are welcome to use this code anywhere as long as you include this notice.
	
	copyright 2015

	QIPA was modified in 2023
*/
#include "Widget/QPColorWheel.h"

 
//LOCTEXT
#define LOCTEXT_NAMESPACE "UMG"
 
/////////////////////////////////////////////////////
// UQPColorWheel

#if WITH_EDITOR
/*
const FSlateBrush* UQPColorWheel::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Image");
}
*/ 
 
const FText UQPColorWheel::GetPaletteCategory()
{
	return LOCTEXT("QP UMG", "QP UMG");
}

#endif

UQPColorWheel::UQPColorWheel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, QPColor(FLinearColor::Red)
{   
	//Default Values Set Here, see above
}

//Rebuild
TSharedRef<SWidget> UQPColorWheel::RebuildWidget()
{
	FColorPickerArgs Args;
	
	//Initial Color
	Args.InitialColor = QPColor; 
	
	Args.bUseAlpha = true;
	Args.bOnlyRefreshOnOk = false;
	Args.bOnlyRefreshOnMouseUp = false;
	
	//Delegates!
	Args.OnColorCommitted 			= FOnLinearColorValueChanged::CreateUObject(	this, &UQPColorWheel::ColorUpdated);
	Args.OnColorPickerCancelled 	= FOnColorPickerCancelled::CreateUObject(		this, &UQPColorWheel::ColorPickCancelled);
	
	//~~~
	 
	ColorPicker = SNew(QPColorPicker)
		.TargetColorAttribute(Args.InitialColor)
		//.TargetFColors(Args.ColorArray ? *Args.ColorArray : TArray<FColor*>())
		//.TargetLinearColors(Args.LinearColorArray ? *Args.LinearColorArray : TArray<FLinearColor*>())
		//.TargetColorChannels(Args.ColorChannelsArray ? *Args.ColorChannelsArray : TArray<FColorChannels>())
		.UseAlpha(Args.bUseAlpha)
		.ExpandAdvancedSection(Args.bExpandAdvancedSection)
		.OnlyRefreshOnMouseUp(Args.bOnlyRefreshOnMouseUp && !Args.bIsModal)
		.OnlyRefreshOnOk(Args.bOnlyRefreshOnOk || Args.bIsModal)
		.OnColorCommitted(Args.OnColorCommitted)
		//.PreColorCommitted(Args.PreColorCommitted)
		.OnColorPickerCancelled(Args.OnColorPickerCancelled)
		.OnInteractivePickBegin(Args.OnInteractivePickBegin)
		.OnInteractivePickEnd(Args.OnInteractivePickEnd)
		.DisplayGamma(Args.DisplayGamma);
	
	//Skip Animation?
	if(bSkipAnimationOnConstruction)
	{  
		SetColor(QPColor, true); //Skip
	}
	
	return ColorPicker.ToSharedRef();
}
//Release
void UQPColorWheel::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ColorPicker.Reset();
}

#if WITH_EDITOR
void UQPColorWheel::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
  
	//Update Picker to QPColor property change!
	if (PropertyName == TEXT("QPColor"))
	{  
		if(ColorPicker.IsValid())
		{
			ColorPicker->SetColorRGB(QPColor);
		}
	}	
} 
#endif

//~~~~~~~~~~~~~~~~~~
//			BP Exposed
//~~~~~~~~~~~~~~~~~~
FLinearColor UQPColorWheel::GetColor() 
{
	return QPColor;
} 
void UQPColorWheel::SetColor(FLinearColor NewColor, bool SkipAnimation )
{ 
	if(!ColorPicker.IsValid()) return;
	 
	//Skip Anim?
	if(SkipAnimation)
	{
		ColorPicker->InstantColor = NewColor; 
		ColorPicker->Animation_SkipToFinalForOneTick = true;		//See SQPColorPicker.h
	}
	else
	{
		//Set!
		ColorPicker->SetColorRGB(NewColor);
	}
}

//~~~~~~~~~~~~~~~~~~~~
//	   Color Picker Internal
//~~~~~~~~~~~~~~~~~~~~
void UQPColorWheel::ColorUpdated(FLinearColor NewValue)
{
	QPColor = NewValue; 
	 
	if(OnColorChanged.IsBound())
	{
		OnColorChanged.Broadcast(QPColor);
	}
} 
void UQPColorWheel::ColorPickCancelled(FLinearColor NewValue)
{
	//Color Picking Cancelled! 
}




/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
