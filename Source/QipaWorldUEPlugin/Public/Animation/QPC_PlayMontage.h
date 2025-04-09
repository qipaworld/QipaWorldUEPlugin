// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "Data/QPData.h"

#include "QPC_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_PlayMontage : public UQPComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, class UAnimMontage*> qp_montage;

	void QP_PlayEvent(UQPData* data);
private:

	class ACharacter* qp_character;
public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FString qp_eventKey = "NotAnim";*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//FString qp_endKey = "QP_AnimNotifyFireName";

};
