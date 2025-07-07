// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/QPData.h"
#include "QPU_AnimInstance.generated.h"
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPU_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	//virtual void UQPU_AnimInstance() override;
	/*virtual void NativeInitializeAnimation();
	virtual void NativeUninitializeAnimation();*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UQPData* qp_data = nullptr;

	inline void QP_SetQPData(UQPData* d) {
		qp_data = d;
	}
};
