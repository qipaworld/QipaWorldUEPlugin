// QIPAWORLD


#include "Notify/QP_AnimNotifyData.h"
#include "Interface/QPI_GetQPData.h"
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"

void UQP_AnimNotifyData::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	
	IQPI_GetQPData* di = Cast<IQPI_GetQPData>(MeshComp->GetOwner());
	if (di) {
		di->QP_GetQPData()->QP_GetUQPData(UQPGIM_AnimNotifyData::QP_DATA_BASE_NAME)->QP_Addbool(qp_animNotifyName,true);
	}
	//if (UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData) { //用这个判断了是否实在运行中
	//	UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData->QP_AddNotifyData(qp_animNotifyName);
	//}
}