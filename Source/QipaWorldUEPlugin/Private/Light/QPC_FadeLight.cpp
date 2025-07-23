// QIPAWORLD


#include "Light/QPC_FadeLight.h"

UQPC_FadeLight::UQPC_FadeLight() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UQPC_FadeLight::BeginPlay() {
    Super::BeginPlay();

    this->SetComponentTickEnabled(true);
   
    

}
void UQPC_FadeLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	qp_idleTime += DeltaTime;
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
			for (auto v : qp_lights) {
				v->SetIntensity(qp_fadeValue);
			}
			
		
	}
}

void UQPC_FadeLight::QP_FadeIn(float time) {
	if (qp_showType == EQPFadeType::SHOW || qp_showType == EQPFadeType::FADE_IN) {
		return;
	}
	qp_showType = EQPFadeType::FADE_IN;
	qp_isPlay = true;

	for (auto v : qp_lights) {
		v->SetIntensity(qp_fadeValue);
	}
	qp_fadeSpeed = (qp_max - qp_fadeValue) / time;
}
void UQPC_FadeLight::QP_FadeOut(float time) {
	if (qp_showType == EQPFadeType::HIDE || qp_showType == EQPFadeType::FADE_OUT) {
		return;
	}
	qp_isPlay = true;
	qp_showType = EQPFadeType::FADE_OUT;
	for (auto v : qp_lights) {
		v->SetIntensity(qp_fadeValue);
	}
	qp_fadeSpeed = (qp_min - qp_fadeValue) / time;
}
void UQPC_FadeLight::QP_FadeTo(float time, float value) {
	if (qp_idleTime < qp_lazyTime) {
		return;
	}
	qp_showType = EQPFadeType::FADE_TO;

	qp_isPlay = true;
	for (auto v : qp_lights) {
		v->SetIntensity(qp_fadeValue);
	}
	qp_fadeSpeed = (value - qp_fadeValue) / time;
}
