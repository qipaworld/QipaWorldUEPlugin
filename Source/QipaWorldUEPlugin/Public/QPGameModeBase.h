// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

};
