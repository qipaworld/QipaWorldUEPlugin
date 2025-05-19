// QIPAWORLD


#include "QPUtil.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
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
	}
}

FIntPoint UQPUtil::QP_GetFullScreenResolution(float percentage) {
	TArray<FIntPoint> resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(resolutions);
	//resolutions.Last().X;
	return FIntPoint(FMath::RoundToInt(resolutions.Last().X * percentage), FMath::RoundToInt(resolutions.Last().Y * percentage));
	//return resolutions[resolutions.Num() - 1] * percentage;
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

void UQPUtil::QP_LOG(const FString& Message, const FColor& Color, float Duration) {
	UE_LOG(LOGQipaWorld, Warning, TEXT("%s"), *Message);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}

	//FPlatformMisc::LowLevelOutputDebugString(*Message);
}
