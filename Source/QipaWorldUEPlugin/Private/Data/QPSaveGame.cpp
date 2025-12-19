// QIPAWORLD


#include "Data/QPSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Online/QPGI_Online.h"
#include "Data/QPGIM_BaseData.h"

#include "QPUtil.h"
FString UQPSaveGame::qp_saveType = "NONE";

FString UQPSaveGame::QP_GenerateSaveKey(const FString& key) {
	if (qp_saveType == "NONE") {
		if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType != "NONE" && !UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType.IsEmpty()) {
			qp_saveType = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType;
		}
		else {
			return FPaths::ProjectUserDir()+ key + ".qp";
		}
	}
	/*else {

	}*/
	/*if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType == "NONE" || UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_SaveKeyType.IsEmpty()) {
		return key;
	}*/
	//FString s =;
	//return key + "sdfsdf";
	FString CustomSaveDir = FPaths::ProjectUserDir() + qp_saveType;// +UQPGI_Online::qp_staticObject->QP_GetPlatform() + "/";
	IFileManager::Get().MakeDirectory(*CustomSaveDir, true);
	//UQPUtil::QP_LOG(CustomSaveDir + key + ".qp");
	//QP_GetPlatform()
	return CustomSaveDir + key + ".qp";
	
}

bool UQPSaveGame::QP_SaveFString(const FString& name, const FString& v, const FString& key) {
	if (key.IsEmpty()) {
		return false;
	}
	TArray<uint8> BinaryData;
	
	BinaryData.Append((uint8*)TCHAR_TO_UTF8(*v), v.Len());

		
	int32 Padding = FAES::AESBlockSize - (BinaryData.Num() % FAES::AESBlockSize);
	if (Padding < FAES::AESBlockSize)
	{
		BinaryData.AddZeroed(Padding);
	}

	FAES::EncryptData(BinaryData.GetData(), BinaryData.Num(), (uint8*)TCHAR_TO_UTF8(*key), key.Len());
	

	if (FFileHelper::SaveArrayToFile(BinaryData, *(UQPSaveGame::QP_GenerateSaveKey(name))))
	{
		return true;
	}
	return false;
}

bool UQPSaveGame::QP_LoadFString(const FString& name, FString& v, const FString& key) {
	TArray<uint8> FileData;
	if (key.IsEmpty()) {
		return false;
	}
	if (FFileHelper::LoadFileToArray(FileData, *(UQPSaveGame::QP_GenerateSaveKey(name))))
	{
		
		FAES::DecryptData(FileData.GetData(), FileData.Num(), (uint8*)TCHAR_TO_UTF8(*key), key.Len());
		
		FileData.Add(0); 

		v = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(FileData.GetData())));

		return true;
	}
	UQPUtil::QP_LOG("Failed to load to file: " + name);
	return false;
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