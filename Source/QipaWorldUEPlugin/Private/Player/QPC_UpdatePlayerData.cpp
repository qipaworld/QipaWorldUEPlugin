// QIPAWORLD


#include "Player/QPC_UpdatePlayerData.h"

UQPC_UpdatePlayerData::UQPC_UpdatePlayerData() {
	PrimaryComponentTick.bCanEverTick = true;
}
void UQPC_UpdatePlayerData::QP_LoadData() {
	qp_playerData = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData();
	qp_playerData->QP_LoadDataFAES("UQPC_UpdatePlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("UQPC_UpdatePlayerDataSaveA"));
 }
void UQPC_UpdatePlayerData::QP_SaveData() {
	qp_playerData->QP_SaveDataFAES("UQPC_UpdatePlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("UQPC_UpdatePlayerDataSaveA"));
 }
void UQPC_UpdatePlayerData::BeginPlay() {
	Super::BeginPlay();
	
	this->SetComponentTickEnabled(true);
	/*if (!qp_mesh) {

		return;
	}


	   qp_material=(qp_mesh->CreateDynamicMaterialInstance(0, qp_mesh->GetMaterial(0)));
	*/
	QP_LoadData();

}
void  UQPC_UpdatePlayerData::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	QP_SaveData();
}
void UQPC_UpdatePlayerData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*qp_idleTime += DeltaTime;
	if (qp_isPlay) {


			qp_fadeValue += qp_fadeSpeed * DeltaTime;
			if (qp_fadeValue >= qp_max) {
				qp_fadeValue = qp_max;
				qp_isPlay = false;
				qp_showType = EQPFadeType::SHOW;
			}else if (qp_fadeValue <= qp_min) {
				qp_fadeValue = qp_min;
				qp_isPlay = false;
				qp_showType = EQPFadeType::HIDE;
			}
			qp_material->SetScalarParameterValue(qp_parameterValueName, qp_fadeValue);


	}*/
}

//void UQPC_UpdatePlayerData::QP_FadeIn(float time) {
//	if (qp_showType == EQPFadeType::SHOW || qp_showType == EQPFadeType::FADE_IN) {
//		return;
//	}
//	qp_showType = EQPFadeType::FADE_IN;
//	qp_isPlay = true;
//
//	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
//	qp_fadeSpeed = (qp_max - qp_fadeValue) / time;
//}
//void UQPC_UpdatePlayerData::QP_FadeOut(float time) {
//	if (qp_showType == EQPFadeType::HIDE || qp_showType == EQPFadeType::FADE_OUT) {
//		return;
//	}
//	qp_isPlay = true;
//	qp_showType = EQPFadeType::FADE_OUT;
//	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
//	qp_fadeSpeed = (qp_min - qp_fadeValue) / time;
//}
//void UQPC_UpdatePlayerData::QP_FadeTo(float time, float value) {
//	if (qp_idleTime < qp_lazyTime) {
//		return;
//	}
//	qp_showType = EQPFadeType::FADE_TO;
//
//	qp_isPlay = true;
//	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
//	qp_fadeSpeed = (value - qp_fadeValue) / time;
//}
