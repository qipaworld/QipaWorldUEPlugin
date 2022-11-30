// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState_TimedNiagaraEffect.h"
#include "QPANS_TimedNiagaraEffect.generated.h"

/**
 * 
 */
class UFXSystemComponent;
class USkeletalMeshComponent;

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPANS_TimedNiagaraEffect : public UAnimNotifyState_TimedNiagaraEffect
{
	GENERATED_BODY()
	virtual UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const;

};
