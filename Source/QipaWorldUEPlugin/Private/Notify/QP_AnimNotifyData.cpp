// QIPAWORLD


#include "Notify/QP_AnimNotifyData.h"
#include "Notify/QPGIM_AnimNotifyData.h"


void UQP_AnimNotifyData::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	
	if (UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData) { //用这个判断了是否实在运行中
		UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData->QP_AddNotifyData(qp_animNotifyName)->QP_AddFString("qp_animNotify", qp_animNotifyName);
	}
}