// QIPAWORLD


#include "QPUtil.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Data/QPGIM_BaseData.h"
DEFINE_LOG_CATEGORY(LOGQipaWorld);




FIntPoint UQPUtil::QP_GetFullScreenResolution(float percentage) {
	TArray<FIntPoint> resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(resolutions);
	return resolutions[resolutions.Num() - 1] * percentage;
}
void UQPUtil::QP_UpdateMouse(bool b, APlayerController* controller) {
	if (!controller) {
		//UE_LOG(LogTemp, Warning, TEXT("Update Mouse Error , Context is Null"));
		//return;
		controller = UGameplayStatics::GetPlayerController(UQPGIM_BaseData::qp_staticObject->GetWorld(), 0);
	}
	
	controller->SetShowMouseCursor(b);
	if (b) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(controller);
	}
	else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(controller);
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
