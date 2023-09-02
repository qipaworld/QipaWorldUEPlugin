// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"
#include "QPDS_DataAsset.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDS_DataAsset : public UQPDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	FString QP_DefaultStartMap = "None";
	/**带加载进度条的地图路径*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	FString QP_DefaultLoadingMap = "None";
	/**默认的ui蓝图路径*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	FString QP_DefaultMainUserInterfacePath = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	FString QP_DefaultCharacterDataPath = "None";

	/*这个是默认的弹出ui动作的key，你可以在动作管理器里加入这个事件，并且绑定按键。他会自动弹出和关闭ui*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	FString QP_DefaultUserInterfaceActionKey = "DefaultUserInterfaceAction";
	/*如果这个为真，上面的key生效*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	bool QP_UserInterfaceAutoPop = true;
	/**UUID*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|defaultSetting")
	TMap<FString, int32> QP_UUID;
};
