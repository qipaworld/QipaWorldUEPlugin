// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Data/QPDataAsset.h"
#include "Character/QPCharacter.h"

#include "QPDA_Character.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDA_Character : public UQPDataAsset
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	TSubclassOf<AQPCharacter> qp_character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FString, class UAnimMontage*> qp_montage;

	//UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "QipaWorld|QPSlime", Meta = (ToolTip = "Material overrides."))
	//TArray<TObjectPtr<class UMaterialInterface>> OverrideMaterials;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//TSubclassOf<UAnimInstance> qp_animClass;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//float qp_walkSpeed = 250.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//float qp_runSpeed = 600.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	float qp_walkMaxAcceleration = 2000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	float qp_runMaxAcceleration = 4000.0f;
	///**是否可以飞*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_fly = false;
	///**是否可以在陆地走路*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_walk = false;
	///**是否可以水下*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_water = false;
	///**是否可以游泳*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_swim = false;
	///**是否可以在水上行走*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_walkUpWater = false;
	///**是否可以在水上行走*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//	bool qp_walkDownWater = false;
};
