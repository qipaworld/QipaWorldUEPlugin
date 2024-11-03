// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPBaseDataSave.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPBaseDataSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float qp_version = 1.0;
	
};
