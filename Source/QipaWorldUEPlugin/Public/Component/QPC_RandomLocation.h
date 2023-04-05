// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "QPC_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_RandomLocation : public UQPComponent
{
	GENERATED_BODY()
public:
	/**随机位置
	@param radius 半径
	@param target 以哪个坐标为中心半径
	@param altitudeMin 最小高度，可以是负数
	@param altitudeMax 最大高度，不可以是负数
	*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPTarget")
	FVector QP_RandomLocation(float radius, FVector target, float altitudeMin = 0, float altitudeMax = 0);
	/**简单的随机位置
	@param radius 半径
	*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPTarget")
	FVector QP_RandomLocationBase(float radius);

};
