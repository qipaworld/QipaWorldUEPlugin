// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Character/QPCharacter.h"
#include "Skill/QP_SkillData.h"
#include "QPDA_Character.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDA_Character : public UQPDataAsset
{
	GENERATED_BODY()
	public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	//TSubclassOf<AQPCharacter> qp_character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, class UAnimMontage*> qp_montage;

	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	//TMap<FName, UQP_SkillData*> qp_skillDatas;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TSubclassOf<AActor> qp_showActor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//float qp_runSpeed = 600.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//float qp_walkMaxAcceleration = 2000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//float qp_runMaxAcceleration = 4000.0f;
	/**是否可以飞*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_fly = false;
	///**是否可以在陆地走路*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_walk = true;
	//**是否可以水下*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_water = false;
	///**是否可以游泳*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_swim = false;
	///**是否可以在水上行走*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_walkUpWater = false;
	///**是否可以在水上行走*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//bool qp_walkDownWater = false;
};
