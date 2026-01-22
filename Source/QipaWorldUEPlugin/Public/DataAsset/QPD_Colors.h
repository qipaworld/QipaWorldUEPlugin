// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

#include "Math/Color.h"
#include "QPD_Colors.generated.h"

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Colors : public UQPDataAsset
{
	GENERATED_BODY()
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, FLinearColor > qp_colorMap;

	

	
};
