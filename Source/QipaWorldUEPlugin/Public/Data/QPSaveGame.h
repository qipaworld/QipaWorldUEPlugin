// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSaveGame : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|UQPSaveGame")
	FString qp_saveKey;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|UQPSaveGame")
	int32 qp_saveId = 0;
public:
	UFUNCTION(BlueprintCallable)
	void QP_SetSaveKey(const FString& v);
	UFUNCTION(BlueprintCallable)
	const FString& QP_GetSaveKey();

	UFUNCTION(BlueprintCallable)
	void QP_SetSaveId(int32 v);
	UFUNCTION(BlueprintCallable)
	int32 QP_GetSaveId();

	UFUNCTION(BlueprintCallable)
	void QP_Save();

	UFUNCTION(BlueprintCallable)
	void QP_AsyncSave();

	//void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);

};
