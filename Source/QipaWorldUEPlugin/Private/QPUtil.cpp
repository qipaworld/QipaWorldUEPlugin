// QIPAWORLD


#include "QPUtil.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
FIntPoint UQPUtil::QP_GetFullScreenResolution(float percentage) {
	TArray<FIntPoint> resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(resolutions);
	return resolutions[resolutions.Num() - 1] * percentage;
}
void UQPUtil::QP_UpdateMouse(UObject* Context,bool b) {
	
	APlayerController* controller = UGameplayStatics::GetPlayerController(Context->GetWorld(), 0);
	controller->SetShowMouseCursor(b);
	if (b) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(controller);
	}
	else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(controller);
	}

}