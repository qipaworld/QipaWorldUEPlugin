// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "Sound/QP_RandomSoundData.h"
//#include "Interface/QPI_AnimNotifyFootstep.h"
#include "Components/AudioComponent.h"
#include "QPC_PlayRandomSound.generated.h"


/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_PlayRandomSound : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPC_PlayRandomSound();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float qp_playTimeMin = 0.15;
	TMap<UObject*,float> qp_playTimes;
	//UAudioComponent* qp_footstepAudio = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|RandomSound")
	TMap<EQPFootstepType, FQP_SoundData > qp_randomSounds;
	void QP_Play(EQPFootstepType, UAudioComponent* qp_audio);
	/*inline void QP_SetVolume(float v) {
		qp_footstepAudio->SetVolumeMultiplier(v);
	}*/
	void QP_Play(AActor*, UAudioComponent* qp_audio);

};
