// QIPAWORLD


#include "QPUtil.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/GameUserSettings.h"
//#include "EditorUtilitySubsystem.h"
//#include "Editor.h"
//#include "WidgetBlueprint.h"
//#include "Blueprint/UserWidget.h"
//#include "Blueprint/UserWidget.h"
//#include "Blueprint/UserWidget.h"
//#include "Blueprint/WidgetTree.h"
//#include "Components/TextBlock.h"
//#include "Widget/QPTextBlock.h"
//#include "AssetRegistry/AssetRegistryModule.h"
//#include "AssetRegistryModule.h"
//#include "EditorUtilitySubsystem.h"
//#include "Editor.h"

#include "Data/QPGIM_BaseData.h"
DEFINE_LOG_CATEGORY(LOGQipaWorld);




//void UQPUtil::QP_ScreenFullWindowed() {
//	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
//	{
//		Settings->SetFullscreenMode(EWindowMode::Windowed);
//
//		Settings->ApplySettings(false);
//	}
//}
void UQPUtil::QP_ScreenResolution(float percentage) {
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		FIntPoint v = QP_GetFullScreenResolution(percentage);

		Settings->SetScreenResolution(v);
		Settings->SetFullscreenMode(EWindowMode::Windowed);

		Settings->ApplySettings(false);
		Settings->SaveSettings();
	}
}

FIntPoint UQPUtil::QP_GetFullScreenResolution(float percentage) {
	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	return FIntPoint(FMath::RoundToInt(Settings->GetDesktopResolution().X * percentage), FMath::RoundToInt(Settings->GetDesktopResolution().Y * percentage));
	
}
void UQPUtil::QP_UpdateMouse(bool b, APlayerController* controller, UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode, bool bHideCursorDuringCapture, const bool bFlushInput) {
	if (!controller) {
		//UE_LOG(LogTemp, Warning, TEXT("Update Mouse Error , Context is Null"));
		//return;
		controller = UGameplayStatics::GetPlayerController(UQPGIM_BaseData::qp_staticObject->GetWorld(), 0);
	}
	
	controller->SetShowMouseCursor(b);
	if (b) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(controller, InWidgetToFocus, InMouseLockMode, bHideCursorDuringCapture, bFlushInput);
	}
	else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(controller, bFlushInput);
	}

}
void UQPUtil::QP_AutoSetingGameQuality() {

	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	if (Settings)
	{
		Settings->RunHardwareBenchmark();
		Settings->ApplyHardwareBenchmarkResults();
		Settings->ApplySettings(false);  
		Settings->SaveSettings();        
	}

}
void UQPUtil::QP_SwitchMouseShow( APlayerController* controller, UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode, bool bHideCursorDuringCapture, const bool bFlushInput) {
	if (!controller) {
		//UE_LOG(LogTemp, Warning, TEXT("Update Mouse Error , Context is Null"));
		//return;
		controller = UGameplayStatics::GetPlayerController(UQPGIM_BaseData::qp_staticObject->GetWorld(), 0);
	}
	QP_UpdateMouse(!controller->bShowMouseCursor, controller, InWidgetToFocus, InMouseLockMode, bHideCursorDuringCapture,bFlushInput);
}
FInputChord UQPUtil::QP_GetKeyForAction(const FName& ActionName) {
	UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();
	const TArray <FInputActionKeyMapping>& OutMappings = InputSettings->GetActionMappings();

	for (int32 ActionIndex = OutMappings.Num() - 1; ActionIndex >= 0; --ActionIndex)
	{
		if (OutMappings[ActionIndex].ActionName == ActionName)
		{
			return FInputChord(OutMappings[ActionIndex].Key, OutMappings[ActionIndex].bShift, OutMappings[ActionIndex].bCtrl, OutMappings[ActionIndex].bAlt, OutMappings[ActionIndex].bCmd);
		}
	}
	return FInputChord();
}
void UQPUtil::QP_ReplaceActionKey(const FName& ActionName, const FInputChord & OldKey, const FInputChord & NewKey)
{
	UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();
	InputSettings->RemoveActionMapping(FInputActionKeyMapping(ActionName, OldKey.Key, OldKey.bShift, OldKey.bCtrl, OldKey.bAlt, OldKey.bCmd));
	InputSettings->AddActionMapping(FInputActionKeyMapping(ActionName, NewKey.Key, NewKey.bShift, NewKey.bCtrl, NewKey.bAlt, NewKey.bCmd));
	InputSettings->SaveKeyMappings();
	InputSettings->ForceRebuildKeymaps();
}

void UQPUtil::QP_ReplaceAxisKey( FName AxisName, const FKey& OldKey, const FKey& NewKey)
{
	UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();
	const TArray <FInputAxisKeyMapping>& OutMappings = InputSettings->GetAxisMappings();
	for (int32 i = OutMappings.Num() - 1; i >= 0; --i)
	{
		const FInputAxisKeyMapping& Mapping = OutMappings[i];
		if (Mapping.AxisName == AxisName && Mapping.Key == OldKey)
		{
			float OldScale = Mapping.Scale;
			InputSettings->RemoveAxisMapping(Mapping);
			FInputAxisKeyMapping NewMapping(AxisName, NewKey);
			NewMapping.Scale = OldScale;
			InputSettings->AddAxisMapping(NewMapping);

			InputSettings->SaveKeyMappings();
			InputSettings->ForceRebuildKeymaps();
			break; 
		}
	}
}

 FKey UQPUtil::QP_GetKeyForAxis(FName AxisName, float ScaleSign, bool bExactMatch)
{
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();
	const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

	for (const FInputAxisKeyMapping& Mapping : AxisMappings)
	{
		if (Mapping.AxisName == AxisName)
		{
			if (FMath::IsNearlyZero(ScaleSign))
			{
				return Mapping.Key;
			}
			else if (bExactMatch)
			{
				
				if (FMath::IsNearlyEqual(Mapping.Scale, ScaleSign))
				{
					return Mapping.Key;
				}
			}
			else
			{
				if ((ScaleSign > 0 && Mapping.Scale > 0) || (ScaleSign < 0 && Mapping.Scale < 0))
				{
					return Mapping.Key;
				}
			}
		}
	}
	return FKey();
}
void UQPUtil::QP_LOG(const FString& Message, const FColor& Color, float Duration) {
	UE_LOG(LOGQipaWorld, Warning, TEXT("%s"), *Message);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}

	//FPlatformMisc::LowLevelOutputDebugString(*Message);
}

FString UQPUtil::MakeRandomString(int32 Length)
{
	FString Result;
	const FString Charset = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~!@#$%^&*()_+=-[]}{';/?.>,<|");

	for (int32 i = 0; i < Length; i++)
	{
		int32 Index = FMath::RandRange(0, Charset.Len() - 1);
		Result.AppendChar(Charset[Index]);
	}
	return Result;
}
