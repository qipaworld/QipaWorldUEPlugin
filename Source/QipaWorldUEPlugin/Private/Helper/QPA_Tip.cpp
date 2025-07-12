// QIPAWORLD


#include "Helper/QPA_Tip.h"
#include "Helper/QPGIM_Tip.h"
bool AQPA_Tip::QP_HelperTip() {
	
	if (UQPGIM_Tip::qp_staticObject->QP_GetHelperNameState(qp_helperName) == EQPHelperType::NOT) {
		QP_HelperTipCell();
		UQPGIM_Tip::qp_staticObject->QP_SetHelperName(qp_helperName,EQPHelperType::OVER);
		return true;
	}
	return false;
	
}

// Called when the game starts or when spawned
void AQPA_Tip::BeginPlay()
{
	Super::BeginPlay();
	//QP_HelperTip();
}
