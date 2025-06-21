// QIPAWORLD


#include "Notify/QP_AnimNotify.h"
#include "Interface/QPI_AnimNotify.h"
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"


void UQP_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;
	IQPI_AnimNotify* di = Cast<IQPI_AnimNotify>(Owner);
	if (di) {
		di->QPI_AnimNotify(qp_animNotifyName);
		//di->QP_GetQPData()->QP_GetUQPData(UQPGIM_AnimNotify::QP_DATA_BASE_NAME)->QP_Addbool(qp_animNotifyName,true);
		//return true;
	}
	//return false;
	//if (UQPGIM_AnimNotify::QP_UQPGIM_AnimNotify) { //用这个判断了是否实在运行中
	//	UQPGIM_AnimNotify::QP_UQPGIM_AnimNotify->QP_AddNotifyData(qp_animNotifyName);
	//}
}
FString UQP_AnimNotify::GetNotifyName_Implementation() const
{
	return TEXT("QP Anim Notify");
}
//FString UQP_AnimNotify::GetNotifyName() const {
//	
//}
