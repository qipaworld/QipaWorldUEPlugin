// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "QP_AnimNotifyFootstep.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQP_AnimNotifyFootstep : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPAnimNotifyData",meta = (Rename = "qp_animNotifyName"))
	FName qp_boneName = "qp_BoneName";

	//UPROPERTY(EditAnywhere, Category = "QipaWorld|QPAnimNotifyData")
	//EQPFootstepAutoVolumeType qp_autoVolumeType = EQPFootstepAutoVolumeType::XYZ;
	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPAnimNotifyData")
	float qp_minVolume = 0.2f;

	//FString GetNotifyName_Implementation() const;
};
