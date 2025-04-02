// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGIM_BaseData.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/QPDS_Default.h"
#include "AudioDeviceManager.h"
#include "AudioDevice.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
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
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	qp_staticObject = this;

	qp_gameBaseData = UQPGIM_Data::qp_staticObject->QP_GetQPData("UQPGIM_BaseData");
	QP_InitDefaultSetting();

	qp_baseDataSave = Cast<UQPBaseDataSave>(UGameplayStatics::LoadGameFromSlot("qp_baseDataSave", 0));
	if (!qp_baseDataSave) {
		qp_baseDataSave = Cast<UQPBaseDataSave>(UGameplayStatics::CreateSaveGameObject(UQPBaseDataSave::StaticClass()));
		qp_baseDataSave->QP_SetSaveKey("qp_baseDataSave");
	}
	
	qp_baseDataSave->AddToRoot();
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
	qp_staticObject = nullptr;

	if (qp_baseDataSave) {
		qp_baseDataSave->QP_Save();
	}

	Super::Deinitialize();
}
float UQPGIM_BaseData::GetVersion() {
	return qp_baseDataSave->qp_version;
}
//void UQPGIM_BaseData::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess) {
//
//}
void UQPGIM_BaseData::SetVersion(float v) {
	if (!qp_baseDataSave) {
		return;
	}
	qp_baseDataSave->qp_version = v;
	qp_baseDataSave->QP_AsyncSave();
	//FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
	// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
	//qp_SavedDelegate.BindUObject(this, &UQPGIM_BaseData::QP_SavedDelegate);
	//UGameplayStatics::AsyncSaveGameToSlot(qp_baseDataSave, "qp_baseDataSave", 0, qp_SavedDelegate);

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
	
	USoundControlBusMix* LoadedBusMix = qp_defaultDataAsset->QP_DefaultUserAudioSetting.LoadSynchronous();
	if (LoadedBusMix)
	{
		//UAudioModulationStatics::ActivateBusMix();
		//UE_LOG(LogTemp, Log, TEXT("³É¹¦¼ÓÔØ Control Bus Mix: %s"), *LoadedBusMix->GetName());
		UAudioModulationStatics::ActivateBusMix(GetWorld(), LoadedBusMix);
	}
	else {
		UQPUtil::QP_LOG("load Control Bus Mix Error");
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
int32 UQPGIM_BaseData::QP_GetUUID(FString& key) {
	if (qp_defaultDataAsset->QP_UUID.Contains(key)) {
		return qp_defaultDataAsset->QP_UUID[key];
	}
	else {
		UQPUtil::QP_LOG("do not find UUID "+key);
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


//UQPDS_DataAsset* UQPGIM_BaseData::QP_GetDefaultSettingDataAsset() {
//	return qp_defaultDataAsset;
//}




