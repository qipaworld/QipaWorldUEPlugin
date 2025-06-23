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

	float qp_playTime = 0;
	bool qp_canPlay = true;
	UAudioComponent* qp_footstepAudio = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|RandomSound")
	TMap<EQPFootstepType, FQP_SoundData > qp_randomSounds;
	void QP_Play(EQPFootstepType);
	inline void QP_SetVolume(float v) {
		qp_footstepAudio->SetVolumeMultiplier(v);
	}
	void QP_Play(AActor*);

};
