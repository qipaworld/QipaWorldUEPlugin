// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QPA_HelperBase.generated.h"

/**
 * 教程基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_HelperBase : public AQPActor
{
	GENERATED_BODY()
	
protected:
	//当前教程id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPHelper")
	FString qp_helperName = "helper";
};
