// QIPAWORLD


#include "Notify/QPANS_TimedNiagaraEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
//
//void UQPANS_TimedNiagaraEffect::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {
//
//}
//void UQPANS_TimedNiagaraEffect::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
//	GLog->Log("jd1111dddumpStrt");
//	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
//}
//void UQPANS_TimedNiagaraEffect::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
//	GLog->Log("jddddumpdddStrt");
//
//}


UFXSystemComponent* UQPANS_TimedNiagaraEffect::SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const
{
	// Only spawn if we've got valid params
	if (ValidateParameters(MeshComp))
	{
		return UNiagaraFunctionLibrary::SpawnSystemAttached(Template, MeshComp, SocketName, LocationOffset, RotationOffset, EAttachLocation::SnapToTarget, !bDestroyAtEnd);
	}
	return nullptr;
}


