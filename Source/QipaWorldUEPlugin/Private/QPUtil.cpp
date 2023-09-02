// QIPAWORLD


#include "QPUtil.h"
#include "Kismet/KismetSystemLibrary.h"
FIntPoint UQPUtil::QP_GetFullScreenResolution(float percentage) {
	TArray<FIntPoint> resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(resolutions);
	return resolutions[resolutions.Num() - 1] * percentage;
}