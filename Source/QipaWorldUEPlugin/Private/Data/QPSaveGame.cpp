// QIPAWORLD


#include "Data/QPSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "QPUtil.h"

void UQPSaveGame::QP_SetSaveKey(const FString& v) {
	qp_saveKey = v;
}

const FString& UQPSaveGame::QP_GetSaveKey(){
	return qp_saveKey;
}


void UQPSaveGame::QP_SetSaveId(int32 v){
	qp_saveId = v;
}

int32 UQPSaveGame::QP_GetSaveId(){
	return qp_saveId;
}


void UQPSaveGame::QP_Save(){
	if (qp_saveKey.IsEmpty()) {
		UQPUtil::QP_LOG("save game error :the save key is empty.");
	}
	else {
		UGameplayStatics::SaveGameToSlot(this, qp_saveKey, qp_saveId);
	}
}


void UQPSaveGame::QP_AsyncSave(){
	if (qp_saveKey.IsEmpty()) {
		UQPUtil::QP_LOG("save game error :the save key is empty.");
	}
	else {
		//FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		//qp_SavedDelegate.BindUObject(this, &UQPSaveGame::QP_SavedDelegate);
		//UGameplayStatics::AsyncSaveGameToSlot(this, qp_saveKey, qp_saveId,qp_SavedDelegate);
		UGameplayStatics::AsyncSaveGameToSlot(this, qp_saveKey, qp_saveId);

	}
}

//void UQPSaveGame::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess){}