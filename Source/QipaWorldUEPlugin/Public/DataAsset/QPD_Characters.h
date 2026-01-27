// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

//#include "Character/QPCharacter.h"
#include "QPD_Characters.generated.h"

class AQPCharacter;
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Characters : public UQPDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, TSubclassOf<AQPCharacter>> qp_characterMap;

	

	
};
