// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "QPHUD.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPHUD : public AHUD
{
	GENERATED_BODY()
	//virtual void SetupInputComponent() override;
public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
};
