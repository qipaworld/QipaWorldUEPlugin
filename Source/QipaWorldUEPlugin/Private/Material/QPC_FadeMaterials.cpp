// QIPAWORLD


#include "Material/QPC_FadeMaterials.h"

UQPC_FadeMaterials::UQPC_FadeMaterials() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UQPC_FadeMaterials::BeginPlay() {
    Super::BeginPlay();

    this->SetComponentTickEnabled(true);
	
    if (!qp_mesh) {

        return;
    }
    for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
    {
        
       qp_materials.Add(qp_mesh->CreateDynamicMaterialInstance(i, qp_mesh->GetMaterial(i)));
	   qp_fadeValues.Add(0);
	   qp_fadeSpeeds.Add(0);
    }
	


}
void UQPC_FadeMaterials::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	qp_idleTime +=  DeltaTime;

	if (qp_isPlay) {
		
		//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
			//UE_LOG(LogTemp, Warning, TEXT("___!_aa__1_ddddddddddddddddd__"));
		for (int32 i = 0; i < qp_materials.Num(); ++i)
		{
			qp_fadeValues[i] += qp_fadeSpeeds[i] * DeltaTime;
			//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
				//UE_LOG(LogTemp, Warning, TEXT("___!_aa__1_ddddddddddddddddd_ddddddddd_%f"), qp_fadeValues[i]);
			if (qp_fadeValues[i] >= qp_maxs[i]) {
				qp_fadeValues[i] = qp_maxs[i];
				qp_isPlay = false;
				//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
					//UE_LOG(LogTemp, Warning, TEXT("___!_aa__1_ddddddddddddddddd__%f"), qp_fadeValues[i]);
				qp_showType = EQPFadeType::SHOW;

			}else if (qp_fadeValues[i] <= qp_mins[i]) {
				qp_fadeValues[i] = qp_mins[i];
				qp_isPlay = false;
				//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
					//UE_LOG(LogTemp, Warning, TEXT("___!_aa__1_ddddddddddddddddd__%f"), qp_fadeValues[i]);
				qp_showType = EQPFadeType::HIDE;

			}
			qp_materials[i]->SetScalarParameterValue(qp_parameterValueName, qp_fadeValues[i]);
			
		}
	}
}

void UQPC_FadeMaterials::QP_FadeIn(float time) {

	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___!_aa__1___%s"), *GetOwner()->GetActorLabel());
	if (qp_idleTime < qp_lazyTime) {
		return;
	}
	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___!_aa__2___%s"), *GetOwner()->GetActorLabel());
	if (qp_showType == EQPFadeType::SHOW || qp_showType == EQPFadeType::FADE_IN) {
		return;
	}
	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
	//UE_LOG(LogTemp, Warning, TEXT("___!_aa___3__%s"),*GetOwner()->GetActorLabel());
	
	qp_isPlay = true;
	qp_showType = EQPFadeType::FADE_IN;
	qp_idleTime = 0;
	for (int32 i = 0; i < qp_materials.Num(); ++i)
	{
		qp_materials[i]->GetScalarParameterValue(qp_parameterValueName, qp_fadeValues[i]);
		qp_fadeSpeeds[i] = (qp_maxs[i] - qp_mins[i]) / time;
	}

}
void UQPC_FadeMaterials::QP_FadeOut(float time) {
	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___a_aa___3__%s"), *GetOwner()->GetActorLabel());
	if (qp_idleTime < qp_lazyTime) {
		return;
	}
	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___a_aa___3__%s"), *GetOwner()->GetActorLabel());
	if (qp_showType == EQPFadeType::HIDE || qp_showType == EQPFadeType::FADE_OUT) {
		return;
	}
	//if ("BP_ChaosJar_116" == GetOwner()->GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___a_aa___3__%s"), *GetOwner()->GetActorLabel());
	qp_isPlay = true;

	qp_showType = EQPFadeType::FADE_OUT;
	qp_idleTime = 0;
	for (int32 i = 0; i < qp_materials.Num(); ++i)
	{
		qp_materials[i]->GetScalarParameterValue(qp_parameterValueName, qp_fadeValues[i]);
		qp_fadeSpeeds[i] = (qp_mins[i] - qp_maxs[i]) / time;
	}
}
void UQPC_FadeMaterials::QP_FadeTo(float time, float value) {
	if (qp_idleTime < qp_lazyTime) {
		return;
	}
	qp_showType = EQPFadeType::FADE_TO;
	qp_isPlay = true;

	qp_idleTime = 0;
	for (int32 i = 0; i < qp_materials.Num(); ++i)
	{
		qp_materials[i]->GetScalarParameterValue(qp_parameterValueName, qp_fadeValues[i]);
		
		qp_fadeSpeeds[i] = ((qp_maxs[i] - qp_mins[i]) * value - qp_fadeValues[i]) / time;
	}
}
