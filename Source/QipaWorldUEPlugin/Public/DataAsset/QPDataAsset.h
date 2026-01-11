// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QPDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FName qp_name;
};
