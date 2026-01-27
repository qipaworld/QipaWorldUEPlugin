// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

//#include "Item/QPA_Item.h"

#include "QPD_Items.generated.h"
class AQPA_Item;
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Items : public UQPDataAsset
{
	GENERATED_BODY()
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, TSubclassOf<AQPA_Item>> qp_itemMap;

	

	
};
