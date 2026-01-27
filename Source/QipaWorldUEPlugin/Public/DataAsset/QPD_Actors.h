// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

//#include "Engine/Actor2D.h"
#include "QPD_Actors.generated.h"

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Actors : public UQPDataAsset
{
	GENERATED_BODY()
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, TSubclassOf<AActor>> qp_actorMap;

	

	
};
