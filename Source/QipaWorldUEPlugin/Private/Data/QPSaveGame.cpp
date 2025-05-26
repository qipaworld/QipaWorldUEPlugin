// QIPAWORLD


#include "Data/QPSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_BaseData.h"

#include "QPUtil.h"
//FString UQPSaveGame::qp_save_ = "NONE";

FString UQPSaveGame::QP_GenerateSaveKey(const FString& key) {
	if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType == "NONE") {
		return key;
	}
	return UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType + key;
	
}
void UQPSaveGame::QP_SetSaveKey(const FString& v) {
	//if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType == "NONE") {
		qp_saveKey = v;
	/*}
	else {
		qp_saveKey = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType + v;
	}*/
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
void UQPSaveGame::QP_SaveMemory() {
	if (qp_saveKey.IsEmpty()) {
		UQPUtil::QP_LOG("save game error :the save key is empty.");
	}
	else {
		TArray<uint8> OutSaveData;
		if (UGameplayStatics::SaveGameToMemory(this, OutSaveData))
		{
			if (UGameplayStatics::SaveDataToSlot(OutSaveData, qp_saveKey, qp_saveId))
			{
				UQPUtil::QP_LOG("save game error :UGameplayStatics::SaveDataToSlot Error.");
			}
		}
		else {
			UQPUtil::QP_LOG("save game error :UGameplayStatics::SaveGameToMemory Error.");
		}
		
	}
}

void UQPSaveGame::QP_AsyncSave(){
	/*QP_Save();
	return;*/
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