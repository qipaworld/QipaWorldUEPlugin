// QIPAWORLD


#include "Widget/QPSimpleTextBlock.h"

void UQPSimpleTextBlock::QP_ChangeFontSlate() {

	if (qp_changeSlate) {
		
		FSlateFontInfo fontinfoBase = GetFont();
		UObject* font = LoadObject<UFont>(nullptr, *qp_fontPath);
		const FSlateFontInfo fontinfo = FSlateFontInfo(font, fontinfoBase.Size,* UQPGIM_Localization::QP_UQPGIM_Localization->QP_GetCurrentLanguage()); // Font, Font Size  for the chatbox
		SetFont(fontinfo);
	}
}