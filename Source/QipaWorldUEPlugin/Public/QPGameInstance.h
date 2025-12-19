// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "QPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	 virtual void Init() override;

	
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	 virtual void Shutdown() override;
	 virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	/** Starts the GameInstance state machine running */
	 virtual void StartGameInstance() override;
	
};
