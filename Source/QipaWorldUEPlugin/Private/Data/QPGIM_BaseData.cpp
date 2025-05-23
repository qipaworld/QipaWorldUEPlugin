// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGIM_BaseData.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/QPDS_Default.h"
#include "AudioDeviceManager.h"
#include "AudioDevice.h"
#include "Data/QPGIM_Data.h"

//#include "Engine/Engine.h"

#include "AudioModulationStatics.h"
#include "QPUtil.h"

UQPGIM_BaseData* UQPGIM_BaseData::qp_staticObject = nullptr;
//UQPDS_DataAsset* UQPGIM_BaseData::qp_defaultDataAsset = nullptr;

bool UQPGIM_BaseData::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_BaseData::Initialize(FSubsystemCollectionBase& Collection)
{
	//UQPUtil::QP_LOG("????????_____AAA_____????????????");

	Super::Initialize(Collection);

	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	qp_staticObject = this;

	qp_gameBaseData = UQPGIM_Data::qp_staticObject->QP_GetUQPData("UQPGIM_BaseData");
	QP_InitDefaultSetting();
	qp_baseDataSave = UQPSaveGame::QP_LoadSaveData<UQPBaseDataSave>("qp_baseDataSave", 0);
	
	
	qp_baseDataSave->AddToRoot();
	//if (UWorld* World = GetWorld())
	//{
		//QP_OnPostLoadMap(World); 
	//}
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UQPGIM_BaseData::QP_OnPostLoadMap);
	//QP_LoadSoundData();

	//qp_loadMapName = UQPDS_Default::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_BaseData::Deinitialize()
{
	//if (qp_bgSound != nullptr) {
		//qp_bgSound->Stop();
	//}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
//	QP_SaveSoundData();
	//UQPUtil::QP_LOG("????????_____AAA__333___????????????");

	qp_staticObject = nullptr;

	if (IsValid(qp_baseDataSave)) {
		qp_baseDataSave->QP_Save();
	}

	Super::Deinitialize();
}
float UQPGIM_BaseData::QP_GetVersion() {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("get SetVersion Error the qp_baseDataSave is null.");
		return 0.0;
	}
	return qp_baseDataSave->qp_version;
}
//void UQPGIM_BaseData::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess) {
//
//}
void UQPGIM_BaseData::QP_SetVersion(float v) {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("save SetVersion Error the qp_baseDataSave is null. Version = " + FString::SanitizeFloat(v));
		return;
	}
	qp_baseDataSave->qp_version = v;
	qp_baseDataSave->QP_AsyncSave();
	//FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
	// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
	//qp_SavedDelegate.BindUObject(this, &UQPGIM_BaseData::QP_SavedDelegate);
	//UGameplayStatics::AsyncSaveGameToSlot(qp_baseDataSave, "qp_baseDataSave", 0, qp_SavedDelegate);
}
bool  UQPGIM_BaseData::QP_IsInitKey(const FString& k) {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("get init key Error the qp_baseDataSave is null . key  = " + k);
		return false;
	}
	if (qp_defaultDataAsset->QP_InitKeys.Contains(k)) {
		return qp_baseDataSave->qp_initMaps.FindOrAdd(qp_defaultDataAsset->QP_InitKeys[k], false);
	}
	else {
		UQPUtil::QP_LOG("qp_defaultDataAsset do not find InitKey <" + k + "> please go to the QP_SetingDataAsset -- QP_InitKeys -- setting!");
		return false;
	}

	
	
}

void  UQPGIM_BaseData::QP_SetInitKey(const FString& k, bool v) {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("save init key Error the qp_baseDataSave is null . key  = " + k);
		return;
	}
	if (qp_defaultDataAsset->QP_InitKeys.Contains(k)) {
		qp_baseDataSave->qp_initMaps.Add(qp_defaultDataAsset->QP_InitKeys[k], v);
	}
	else {
		UQPUtil::QP_LOG("qp_defaultDataAsset do not find InitKey <" + k + "> please go to the QP_SetingDataAsset -- QP_InitKeys -- setting!");
		//return;
	}
	qp_baseDataSave->QP_AsyncSave();
}


bool  UQPGIM_BaseData::QP_IsTipKey(const FString& k) {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("get tip key Error the qp_baseDataSave is null . key  = " + k);
		return false;
	}

	if (qp_defaultDataAsset->QP_TipKeys.Contains(k)) {
		return qp_baseDataSave->qp_tipMaps.FindOrAdd(qp_defaultDataAsset->QP_TipKeys[k], false);
	}
	else {
		UQPUtil::QP_LOG("qp_defaultDataAsset do not find TipKey <" + k + "> please go to the QP_SetingDataAsset -- QP_TipKeys -- setting!");
		return false;
	}

}

void  UQPGIM_BaseData::QP_SetTipKey(const FString& k, bool v) {
	if (!IsValid(qp_baseDataSave)) {
		UQPUtil::QP_LOG("save tip key Error the qp_baseDataSave is null . key  = " + k);
		return;
	}

	if (qp_defaultDataAsset->QP_TipKeys.Contains(k)) {
		//return qp_baseDataSave->qp_tipMaps.FindOrAdd(qp_defaultDataAsset->QP_TipKeys[k], false);
		qp_baseDataSave->qp_tipMaps.Add(qp_defaultDataAsset->QP_TipKeys[k], v);

	}
	else {
		UQPUtil::QP_LOG("qp_defaultDataAsset do not find TipKey <" + k + "> please go to the QP_SetingDataAsset  -- QP_TipKeys -- setting!");
		//return false;
	}

	qp_baseDataSave->QP_AsyncSave();
}

UQPData* UQPGIM_BaseData::QP_GetGameBaseData()
{
	return qp_gameBaseData;
}
//UQPData* UQPGIM_BaseData::QP_GetDefaultSetting() {
//	return qp_gameBaseData->QP_GetUQPData("QP_GetDefaultSetting");
//}
void UQPGIM_BaseData::QP_InitDefaultSetting() {
	qp_defaultDataAsset = UQPDS_Default::QP_GET()->QP_SetingDataAsset.LoadSynchronous();
	qp_defaultDataAsset->AddToRoot();
	/*qp_defaultDataAsset = LoadObject<UQPDS_DataAsset>(nullptr, TEXT("/Script/QipaWorldUEPlugin.QPDS_DataAsset'/Game/QipaWorld3D/DataAsset/QP_DefaultSetting.QP_DefaultSetting'"));
	if (!qp_defaultDataAsset) {
		qp_defaultDataAsset = LoadObject<UQPDS_DataAsset>(nullptr, TEXT("/Script/QipaWorldUEPlugin.QPDS_DataAsset'/QipaWorldUEPlugin/DataAsset/QP_DefaultSetting.QP_DefaultSetting'"));
	}*/
	if (qp_defaultDataAsset->QP_DynamicResolutionEnabled) {
		GEngine->SetDynamicResolutionUserSetting(true);
	}
	
	
	
	//UQPData* qpData = QP_GetDefaultSetting();
	//qpData->QP_AddFString("QP_DefaultStartMap", qp_defaultDataAsset->QP_DefaultStartMap);
	//qpData->QP_AddFString("QP_DefaultLoadingMap", qp_defaultDataAsset->QP_DefaultLoadingMap);
	//qpData->QP_AddFString("QP_DefaultMainUserInterfacePath", qp_defaultDataAsset->QP_DefaultMainUserInterfacePath);
	//qpData->QP_AddFString("QP_DefaultCharacterDataPath", qp_defaultDataAsset->QP_DefaultCharacterDataPath);
	//qpData->QP_AddFString("QP_DefaultUserInterfaceActionKey", qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey);
	//qpData->QP_Addbool("QP_UserInterfaceAutoPop", qp_defaultDataAsset->QP_UserInterfaceAutoPop);
	//UQPData* qpuuid = qpData->QP_GetUQPData("QPUUID");
	//for (auto uuid : qp_defaultDataAsset->QP_UUID) {
		//qpuuid->QP_Addint32(uuid.Key, uuid.Value);
	//}
	
}
void UQPGIM_BaseData::QP_OnPostLoadMap(UWorld* LoadedWorld)
{
	if (LoadedWorld)
	{
		/*USoundControlBusMix* LoadedBusMix = qp_defaultDataAsset->QP_DefaultUserAudioSetting.LoadSynchronous();
		if (LoadedBusMix)
		{
			UAudioModulationStatics::ActivateBusMix(LoadedWorld, LoadedBusMix);
			if (!UAudioModulationStatics::IsControlBusMixActive(LoadedWorld, LoadedBusMix)) {
				UQPUtil::QP_LOG("load Control Bus Mix Error");
			}
		}
		else {
			UQPUtil::QP_LOG("load Control Bus Mix Error");
		}*/
	}
}
int32 UQPGIM_BaseData::QP_GetUUID(const FString& key) {
	if (qp_defaultDataAsset->QP_UUID.Contains(key)) {
		return qp_defaultDataAsset->QP_UUID[key];
	}
	else {
		UQPUtil::QP_LOG("qp_defaultDataAsset do not find UUID <" + key + "> please go to the QP_SetingDataAsset  -- QP_UUID --  setting!");

		return 0;
	}
	//return QP_GetDefaultSetting()->QP_GetUQPData("QPUUID")->QP_Getint32(key);
}
UQPData* UQPGIM_BaseData::QP_GetPlayerData() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetPlayerData");

}
UQPData* UQPGIM_BaseData::QP_GetGameStatusData() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetGameStatusData");

}

UQPData* UQPGIM_BaseData::QP_GetUIEventData() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetUIEventData");

}
UQPData* UQPGIM_BaseData::QP_GetKeyBoardEventData() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetKeyBoardEventData");

}
UQPData* UQPGIM_BaseData::QP_GetSoundData() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetSoundData");

}





//UQPData* QP_GetUIEventData();



//UQPDS_DataAsset* UQPGIM_BaseData::QP_GetDefaultSettingDataAsset() {
//	return qp_defaultDataAsset;
//}




