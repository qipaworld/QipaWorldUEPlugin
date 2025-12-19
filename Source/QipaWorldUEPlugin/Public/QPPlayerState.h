// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "QPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
};
