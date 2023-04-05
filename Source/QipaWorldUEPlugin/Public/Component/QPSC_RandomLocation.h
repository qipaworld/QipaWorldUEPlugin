// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPSComponent.h"
#include "Component/QPC_RandomLocation.h"

#include "QPSC_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSC_RandomLocation : public UQPSComponent
{
	GENERATED_BODY()
public:
	UQPSC_RandomLocation();
	/** 随机移动位置组件 */
	UPROPERTY(Category = "QipaWorld|QPTarget", EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UQPC_RandomLocation> qp_randmoLocatin;
	/** 随机移动位半径 */
	UPROPERTY(Category = "QipaWorld|QPTarget", EditAnywhere, BlueprintReadWrite)
		float qp_radius = 50.f;
	/** 随机移动位置Z最小值 */
	UPROPERTY(Category = "QipaWorld|QPTarget", EditAnywhere, BlueprintReadWrite)
		float qp_altitudeMin = 0.f;
	/** 随机移动位置Z最大值 */
	UPROPERTY(Category = "QipaWorld|QPTarget", EditAnywhere, BlueprintReadWrite)
		float qp_altitudeMax = 0;
public:
	/**随机位置

	*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPTarget")
		void QP_RandomLocation(FVector v);

};
