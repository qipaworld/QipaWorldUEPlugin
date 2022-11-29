// QIPAWORLD


#include "Helper/QPA_Tip.h"
#include "Helper/QPGIM_Tip.h"
bool AQPA_Tip::QP_HelperTip() {
	if (UQPGIM_Tip::QP_UQPGIM_Tip->QP_GetHelperNameState(qp_helperName)) {
		QP_HelperTipCell();
		UQPGIM_Tip::QP_UQPGIM_Tip->QP_SetHelperName(qp_helperName);
		return true;
	}
	return false;
	
}

// Called when the game starts or when spawned
void AQPA_Tip::BeginPlay()
{
	Super::BeginPlay();
	QP_HelperTip();
}
