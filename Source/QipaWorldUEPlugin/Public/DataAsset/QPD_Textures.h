// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

#include "Engine/Texture2D.h"
#include "QPD_Textures.generated.h"

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Textures : public UQPDataAsset
{
	GENERATED_BODY()
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, TObjectPtr<UTexture2D>> qp_textureMap;

	

	
};
