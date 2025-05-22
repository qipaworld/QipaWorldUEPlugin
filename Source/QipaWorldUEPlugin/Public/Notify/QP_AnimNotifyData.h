// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "QP_AnimNotifyData.generated.h"


class UAnimSequenceBase;
class USkeletalMeshComponent;

/**
 * 以数据的形式通知，你只需要绑定名字即可在动画绑定类里获得通知。
 */
UCLASS(DisplayName = "QP Anim Notify", meta = (ToolTip = "if you Charactor inheritance IQP_AnimNotify,Will trigger the QP_AnimNotify function"))
class QIPAWORLDUEPLUGIN_API UQP_AnimNotifyData : public UAnimNotify
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPAnimNotifyData")
	FName qp_animNotifyName = "qp_animNotifyName";
	/**发送数据*/
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	FString GetNotifyName_Implementation() const;

	 //bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const ;
	 
public:
	
};
