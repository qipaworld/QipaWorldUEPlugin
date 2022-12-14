// QIPAWORLD


#include "Widget/QPTextBlock.h"
//#include "Data/QPGIM_Data.h"

UQPTextBlock::UQPTextBlock() {
	
	if (UQPGIM_Localization::QP_UQPGIM_Localization!= nullptr) {
		UQPGIM_Localization::QP_UQPGIM_Localization->qp_localizationData->qp_dataDelegate.AddUObject(this, &UQPTextBlock::QP_L10NChange);
		QP_ChangeFontSlate();
	}
}

void UQPTextBlock::QP_L10NChange(const UQPData* data) {
	
	QP_ChangeFontSlate();
}
void UQPTextBlock::QP_ChangeFontSlate() {
	if (qp_changeSlate) {

		const FSlateFontInfo fontinfoBase = GetFont();

		UObject* font = LoadObject<UFont>(nullptr, *UQPGIM_Localization::QP_UQPGIM_Localization->QP_GetL10NAssetsPath(qp_fontPath));

		const FSlateFontInfo fontinfo = FSlateFontInfo(font, fontinfoBase.Size, fontinfoBase.TypefaceFontName); // Font, Font Size  for the chatbox
		SetFont(fontinfo);
	}
}