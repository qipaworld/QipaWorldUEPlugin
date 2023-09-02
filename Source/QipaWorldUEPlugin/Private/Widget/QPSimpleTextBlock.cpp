// QIPAWORLD


#include "Widget/QPSimpleTextBlock.h"

void UQPSimpleTextBlock::QP_ChangeFontSlate() {

	if (qp_changeSlate && MyTextBlock.IsValid()) {
		
		FSlateFontInfo fontinfoBase = GetFont();
		fontinfoBase.TypefaceFontName = FName(*UQPGIM_Localization::qp_staticObject->QP_GetCurrentLanguage());
		//const FSlateFontInfo fontinfo = FSlateFontInfo(fontinfoBase.FontObject, fontinfoBase.Size,* UQPGIM_Localization::qp_staticObject->QP_GetCurrentLanguage()); // Font, Font Size  for the chatbox
		SetFont(fontinfoBase);
	}
}