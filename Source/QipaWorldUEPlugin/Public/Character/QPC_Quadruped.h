
// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Character/QPCharacter.h"
#include "QPC_Quadruped.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPC_Quadruped : public AQPCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AQPC_Quadruped();

public:

	/**发射的魔法技能的类*/
	//UPROPERTY(EditAnywhere, Category = "QipaWorld|QPSlime")
		//TSubclassOf<AQPS_CollisionMovement> qp_attackSkill;

	//void QP_RestorSlime();
public:

	//void QP_AnimNotifySwitchPlayer(UQPData* data);
	//virtual void QPI_AnimNotify(const FName& n);


	/**创建魔法技能*/
	//virtual void QP_Fire() override;

	//按下鼠标右键
	//virtual void QP_AttackTwoStart()override;
	//松开鼠标右键
	//virtual void QP_AttackTwoEnd()override;
};
