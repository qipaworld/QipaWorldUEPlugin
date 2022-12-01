// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Helper/QPA_HelperBase.h"
#include "QPA_Course.generated.h"

/**
 * 教程类，可以理解为连续的教程
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Course : public AQPA_HelperBase
{
	GENERATED_BODY()

protected:
	//下一个教程id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCourse")
	FString qp_nextHelperName;
};
