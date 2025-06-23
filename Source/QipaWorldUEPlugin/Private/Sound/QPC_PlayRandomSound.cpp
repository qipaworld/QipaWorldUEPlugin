// QIPAWORLD


#include "Sound/QPC_PlayRandomSound.h"

UQPC_PlayRandomSound::UQPC_PlayRandomSound() {
    PrimaryComponentTick.bCanEverTick = true;
}
void UQPC_PlayRandomSound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!qp_canPlay) {
        qp_playTime += DeltaTime;
        if (qp_playTime > 0.15) {
            qp_canPlay = true;
        }
    }
    // ...
}

void UQPC_PlayRandomSound::QP_Play(EQPFootstepType t) {
    if (!qp_canPlay) {
        return;
    }
    qp_canPlay = false;
    qp_playTime = 0;
	FQP_SoundData& soundData = qp_randomSounds[t];

	FQP_SoundDataCell& soundDataCell = soundData.qp_soundCell[FMath::RandRange(0, soundData.qp_soundCell.Num() - 1)];

	qp_footstepAudio->SetWaveParameter("qp_wave", soundDataCell.qp_sound);
	qp_footstepAudio->SetFloatParameter("qp_volume", soundDataCell.qp_volume);
	//qp_footstepAudio->SetVolumeMultiplier(qp_movementC->Velocity.Size() / qp_runSpeed * (1 - minVolume) + minVolume);
	qp_footstepAudio->Play(0);
}
void UQPC_PlayRandomSound::QP_Play(AActor* a) {
    EQPFootstepType t = EQPFootstepType::DEFAULT;
    if (a->Tags.Contains("wood")) {
        t = EQPFootstepType::WOOD;
    }
    else if (a->Tags.Contains("tile")) {
        t = EQPFootstepType::TILE;
    }
    else if (a->Tags.Contains("woodAir")) {
        t = EQPFootstepType::WOOD_AIR;
    }
    QP_Play(t);
}