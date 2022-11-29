// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QPA_HelperBase.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_HelperBase : public AQPActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString qp_helperName = "helper";
};
