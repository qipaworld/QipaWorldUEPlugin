// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Data/QPSaveGame.h"
#include "QPBaseDataSave.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPBaseDataSave : public UQPSaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float qp_version = 1.0;
	
};
