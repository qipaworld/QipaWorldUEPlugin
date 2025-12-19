// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"
#include "QPWorldData.generated.h"

/**
 *
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPWorldData : public UQPDataAsset
{
	GENERATED_BODY()
	public:
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
		float qp_temperature = 10;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
		float qp_humidity = 10;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
		float qp_oxygen = 2;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	//float qp_walkSpeed = 250.0f;

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
