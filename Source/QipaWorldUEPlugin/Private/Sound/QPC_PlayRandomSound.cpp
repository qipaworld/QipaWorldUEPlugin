// QIPAWORLD


#include "Sound/QPC_PlayRandomSound.h"

UQPC_PlayRandomSound::UQPC_PlayRandomSound() {
    PrimaryComponentTick.bCanEverTick = true;
}
void UQPC_PlayRandomSound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!qp_playTimes.IsEmpty()) {

        for (auto It = qp_playTimes.CreateIterator(); It; ++It)
        {
            It->Value = It->Value + DeltaTime;
            if (It->Value >= qp_playTimeMin) 
            {
                It.RemoveCurrent(); 
            }
        }

    }
    // ...
}

void UQPC_PlayRandomSound::QP_Play(EQPFootstepType t, UAudioComponent* qp_audio) {
    if (qp_playTimes.Contains(qp_audio)) {
        return;
    }
    qp_playTimes.Add(qp_audio, 0);
    //qp_canPlay = false;
    //qp_playTime = 0;
    if (!qp_randomSounds.Contains(t)) {
        return;
    }
	FQP_SoundData& soundData = qp_randomSounds[t];
    if (soundData.qp_soundCell.IsEmpty()) {
        return;
    }
	FQP_SoundDataCell& soundDataCell = soundData.qp_soundCell[FMath::RandRange(0, soundData.qp_soundCell.Num() - 1)];

    qp_audio->SetWaveParameter("qp_wave", soundDataCell.qp_sound);
    qp_audio->SetFloatParameter("qp_volume", soundDataCell.qp_volume);
	//qp_footstepAudio->SetVolumeMultiplier(qp_movementC->Velocity.Size() / qp_runSpeed * (1 - minVolume) + minVolume);
    qp_audio->Play(0);
}
void UQPC_PlayRandomSound::QP_Play(AActor* a, UAudioComponent* qp_audio) {
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
    QP_Play(t, qp_audio);
}