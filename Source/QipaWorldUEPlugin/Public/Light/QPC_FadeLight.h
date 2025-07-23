// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
//#include "Component/QPComponent.h"
#include "Material/QPC_FadeMaterials.h"
#include "Components/LightComponent.h"
#include "QPC_FadeLight.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_FadeLight : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPC_FadeLight();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay();

	bool qp_isPlay = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_lazyTime = 0.1;
	float qp_idleTime = 0;
	float qp_fadeValue;
	float qp_fadeSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_min;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	//FName qp_parameterValueName;
	/*you need set value in blueprint*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	TArray< ULightComponent*> qp_lights;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	//class UMaterialInstanceDynamic* qp_material;

	void QP_FadeIn(float time);
	void QP_FadeOut(float time);
	void QP_FadeTo(float time,float value);
	EQPFadeType qp_showType = EQPFadeType::DEFAULT;

	/*void QP_Play(EQPFootstepType);
	inline void QP_SetVolume(float v) {
		qp_footstepAudio->SetVolumeMultiplier(v);
	}
	void QP_Play(AActor*);*/
};
