// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState_TimedNiagaraEffect.h"
#include "QPANS_TimedNiagaraEffect.generated.h"

/**
 * 蒙太奇播放持续Niagara有问题，骨骼缩放了就挂了，因为Niagara不能缩放，所以临时写一个
 * 引擎修复之后直接注释SpawnEffect方法即可
 */
class UFXSystemComponent;
class USkeletalMeshComponent;

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPANS_TimedNiagaraEffect : public UAnimNotifyState_TimedNiagaraEffect
{
	GENERATED_BODY()
	/**
		* 蒙太奇播放持续Niagara有问题，骨骼缩放了就挂了，因为Niagara不能缩放，所以临时写一个
		* 引擎修复之后直接注释SpawnEffect方法即可
		*/
	virtual UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const;

};
