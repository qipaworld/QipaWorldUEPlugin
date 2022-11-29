// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Helper/QPA_HelperBase.h"
#include "QPA_Course.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Course : public AQPA_HelperBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString qp_nextHelperName;
};
