// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "QPC_FadeMaterials.generated.h"


UENUM(BlueprintType)
enum class EQPFadeType :uint8
{
	DEFAULT              UMETA(DisplayName = "default"),
	SHOW              UMETA(DisplayName = "show"),
	HIDE             UMETA(DisplayName = "HIDE"),
	FADE_IN             UMETA(DisplayName = "fade in"),
	FADE_OUT             UMETA(DisplayName = "fade out"),
	FADE_TO             UMETA(DisplayName = "fade to"),
};

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_FadeMaterials : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPC_FadeMaterials();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay();

	bool qp_isPlay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_lazyTime = 0.1;
	float qp_idleTime = 0;
	TArray<float> qp_fadeValues;
	TArray<float> qp_fadeSpeeds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	TArray<float> qp_maxs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	TArray<float> qp_mins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	FName qp_parameterValueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	UMeshComponent* qp_mesh = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	TArray<class UMaterialInstanceDynamic*> qp_materials;

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
