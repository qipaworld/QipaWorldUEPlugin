// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void QP_OnAutoUIKeyPressed();
	
};
