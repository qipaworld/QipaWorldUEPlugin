// QIPAWORLD


#include "Material/QPC_FadeMaterial.h"

UQPC_FadeMaterial::UQPC_FadeMaterial() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UQPC_FadeMaterial::BeginPlay() {
    Super::BeginPlay();

    this->SetComponentTickEnabled(true);
    if (!qp_mesh) {

        return;
    }
   
        
       qp_material=(qp_mesh->CreateDynamicMaterialInstance(0, qp_mesh->GetMaterial(0)));
    
    

}
void UQPC_FadeMaterial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	qp_idleTime += DeltaTime;
	if (qp_isPlay) {
		
		
			qp_fadeValue += qp_fadeSpeed * DeltaTime;
			if (qp_fadeValue >= qp_max) {
				qp_fadeValue = qp_max;
				qp_isPlay = false;
				qp_showType = EQPFadeMaterialType::SHOW;
			}else if (qp_fadeValue <= qp_min) {
				qp_fadeValue = qp_min;
				qp_isPlay = false;
				qp_showType = EQPFadeMaterialType::HIDE;
			}
			qp_material->SetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
			
		
	}
}

void UQPC_FadeMaterial::QP_FadeIn(float time) {
	if (qp_showType == EQPFadeMaterialType::SHOW || qp_showType == EQPFadeMaterialType::FADE_IN) {
		return;
	}
	qp_showType = EQPFadeMaterialType::FADE_IN;
	qp_isPlay = true;

	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
	qp_fadeSpeed = (qp_max - qp_fadeValue) / time;
}
void UQPC_FadeMaterial::QP_FadeOut(float time) {
	if (qp_showType == EQPFadeMaterialType::HIDE || qp_showType == EQPFadeMaterialType::FADE_OUT) {
		return;
	}
	qp_isPlay = true;
	qp_showType = EQPFadeMaterialType::FADE_OUT;
	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
	qp_fadeSpeed = (qp_min - qp_fadeValue) / time;
}
void UQPC_FadeMaterial::QP_FadeTo(float time, float value) {
	if (qp_idleTime < qp_lazyTime) {
		return;
	}
	qp_showType = EQPFadeMaterialType::FADE_TO;

	qp_isPlay = true;
	qp_material->GetScalarParameterValue(qp_parameterValueName, qp_fadeValue);
	qp_fadeSpeed = (value - qp_fadeValue) / time;
}
