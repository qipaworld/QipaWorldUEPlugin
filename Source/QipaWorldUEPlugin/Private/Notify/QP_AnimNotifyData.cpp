// QIPAWORLD


#include "Notify/QP_AnimNotifyData.h"
#include "Interface/QP_AnimNotify.h"
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"

void UQP_AnimNotifyData::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	IQP_AnimNotify* di = Cast<IQP_AnimNotify>(MeshComp->GetOwner());
	if (di) {
		di->QP_AnimNotify(qp_animNotifyName);
		//di->QP_GetQPData()->QP_GetUQPData(UQPGIM_AnimNotifyData::QP_DATA_BASE_NAME)->QP_Addbool(qp_animNotifyName,true);
		//return true;
	}
	//return false;
	//if (UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData) { //用这个判断了是否实在运行中
	//	UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData->QP_AddNotifyData(qp_animNotifyName);
	//}
}