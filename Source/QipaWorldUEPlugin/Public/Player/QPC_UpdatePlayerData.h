// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
//#include "Material/QPC_UpdatePlayerDatas.h"
#include "Data/QPGIM_BaseData.h"

#include "QPC_UpdatePlayerData.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_UpdatePlayerData : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPData* qp_playerData;
	UQPC_UpdatePlayerData();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void QP_LoadData();
	virtual void QP_SaveData();

	//bool qp_isPlay = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	//float qp_lazyTime = 0.1;
	//float qp_idleTime = 0;
	//float qp_fadeValue;
	//float qp_fadeSpeed;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	FName qp_parameterValueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	UMeshComponent* qp_mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	class UMaterialInstanceDynamic* qp_material;

	void QP_FadeIn(float time);
	void QP_FadeOut(float time);
	void QP_FadeTo(float time,float value);
	EQPFadeType qp_showType = EQPFadeType::DEFAULT;*/

	/*void QP_Play(EQPFootstepType);
	inline void QP_SetVolume(float v) {
		qp_footstepAudio->SetVolumeMultiplier(v);
	}
	void QP_Play(AActor*);*/
};
