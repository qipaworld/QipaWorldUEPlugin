// QIPAWORLD


#include "Animation/QPC_PlayMontage.h"
#include "Interface/QPI_GetQPData.h"
#include "Character/QPCharacter.h"


void UQPC_PlayMontage::BeginPlay() {
	Super::BeginPlay();
	qp_character = Cast<ACharacter>(GetOwner());
	IQPI_GetQPData* ReactingObject = Cast<IQPI_GetQPData>(qp_character);
	if (ReactingObject) {
		ReactingObject->QP_GetQPData()->qp_dataDelegate.AddUObject(this, &UQPC_PlayMontage::QP_PlayEvent);
	}
}
void UQPC_PlayMontage::QP_PlayEvent(UQPData* data) {
	for (auto& animData : qp_montage)
	{

		if (data->qp_changeMap.Contains(animData.Key)) {
			//更改key但是不切换动画
			if (data->QP_GetFString(animData.Key) == "notPlay") {
				continue;
			}

			//你没有添加要播放的动画蒙太奇
			if (ensure(animData.Value)) {
				//只能让character播放蒙太奇
				if (ensure(qp_character)) {

					qp_character->PlayAnimMontage(animData.Value, 1.0f, FName(*(data->QP_GetFString(animData.Key))));
				}
				//qp_isJump = true;
			}
		}
	}
	
	
}