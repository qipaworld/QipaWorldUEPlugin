// QIPAWORLD


#include "Animation/QPC_PlayMontage.h"
#include "Interface/QPI_GetAnimData.h"
#include "QPUtil.h"
#include "Character/QPCharacter.h"


void UQPC_PlayMontage::BeginPlay() {
	Super::BeginPlay();
	qp_character = Cast<ACharacter>(GetOwner());
	IQPI_GetAnimData* ReactingObject = Cast<IQPI_GetAnimData>(qp_character);
	if (ReactingObject) {
		ReactingObject->QP_GetAnimData()->qp_dataDelegate.AddUObject(this, &UQPC_PlayMontage::QP_PlayEvent);
	}
}
void UQPC_PlayMontage::QP_PlayEvent(UQPData* data) {
	
	//for (auto& animData : qp_montage)
	//{
		//UQPUtil::QP_LOG(animData.Key.ToString());
		//data->QP_Getchange<FName, FName>(EQPDataValueType::FNAME, EQPDataKeyType::FNAME);
			if (data->QP_IsChange<FName, FName>("playAnim", EQPDataValueType::FNAME)) {
				//更改key但是不切换动画
				//if (data->QP_GetFName(animData.Key) == "notPlay") {
					//continue;
				//}
				FName& k = data->QP_GetFName("playAnim");
				if (qp_montage.Contains(k)) {
					UAnimMontage** m = qp_montage.Find(k);
					//你没有添加要播放的动画蒙太奇
					if (ensure(m)) {
						//只能让character播放蒙太奇
						if (ensure(qp_character)) {
							//if (data->QP_IsChange<FName, FName>("startSectionName", EQPDataValueType::FNAME)) {
								qp_character->PlayAnimMontage(*m, 1.0f, data->QP_GetFName("startSectionName"));
								//UE_LOG(LogTemp, Warning, TEXT("___!___d___ddsdf"));
							/*}
							else {
								qp_character->PlayAnimMontage(*m, 1.0f);
							}*/
						}
						//qp_isJump = true;
					}
				}
				
			}
		
	//}
	
	
}