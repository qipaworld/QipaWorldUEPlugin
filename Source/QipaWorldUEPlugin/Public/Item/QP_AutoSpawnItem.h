// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QP_AutoSpawn.h"
#include "QP_AutoSpawnItem.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQP_AutoSpawnItem : public AQP_AutoSpawn
{
	GENERATED_BODY()
	
	
public:
	virtual AQPActor* QP_Spawn() override;
	
};
