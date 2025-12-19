// QIPAWORLD
/*
	By Qipa for You

	You are welcome to use this code anywhere as long as you include this notice.

	copyright 2023
*/

#include "Widget/QPTextBlock.h"
//#include "Data/QPGIM_Data.h"
#include "Kismet/KismetSystemLibrary.h"

UQPTextBlock::UQPTextBlock() {
	//Super();
	/*if (UQPGIM_Localization::qp_staticObject != nullptr) {
		const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("QP_Init"), this);
		UKismetSystemLibrary::Delay(this, 0.1f, LatentInfo);
	}*/
}
//void UQPTextBlock::QP_Init() {
//	qp_fontPath = GetFont().FontObject.GetPathName();
//
//	UQPGIM_Localization::qp_staticObject->qp_localizationData->qp_dataDelegate.AddUObject(this, &UQPTextBlock::QP_L10NChange);
//	QP_ChangeFontSlate();
//}
//void UQPTextBlock::QP_L10NChange(UQPData* data) {
//
//	//if (data->qp_changeMap.Contains("QP_DelayLanguageChange")) {
//		QP_ChangeFontSlate();
//	//}
//}
//void UQPTextBlock::QP_ChangeFontSlate() {
//	//if (qp_changeSlate&& MyTextBlock.IsValid()) {
//
//	//	const FSlateFontInfo fontinfoBase = GetFont();
//
//	//	UFont* font = LoadObject<UFont>(nullptr, *UQPGIM_Localization::qp_staticObject->QP_GetL10NAssetsPath(qp_fontPath));
//
//	//	FSlateFontInfo fontinfo = FSlateFontInfo(font, fontinfoBase.Size, fontinfoBase.TypefaceFontName); // Font, Font Size  for the chatbox
//	//	fontinfo.FontMaterial = fontinfoBase.FontMaterial;
//	//	
//	//	SetFont(fontinfo);
//	//}
//}
#if WITH_EDITOR

const FText UQPTextBlock::GetPaletteCategory()
{
	return FText::FromString("QP UMG");
}
#endif
