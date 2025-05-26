// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
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

	//static FString qp_save_;
public:
	//static FString QP_GetSaveKey();
	static FString QP_GenerateSaveKey(const FString& key);
	template<typename T>
	static T* QP_LoadSaveData(const FString& key,int32 index = 0) {
		FString k = QP_GenerateSaveKey(key);
		T* saveData = Cast<T>(UGameplayStatics::LoadGameFromSlot(k, index));
		if (!IsValid(saveData)) {
			saveData = Cast<T>(UGameplayStatics::CreateSaveGameObject(T::StaticClass()));
			saveData->QP_SetSaveKey(k);
			saveData->QP_SetSaveId(index);
		}
		return saveData;
	}
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
	void QP_SaveMemory();

	UFUNCTION(BlueprintCallable)
	void QP_AsyncSave();

	//void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);

};
