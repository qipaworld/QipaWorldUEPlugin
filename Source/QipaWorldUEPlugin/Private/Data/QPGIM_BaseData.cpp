// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGIM_BaseData.h"


#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_BaseData* UQPGIM_BaseData::qp_staticObject = nullptr;
UQPDS_DataAsset* UQPGIM_BaseData::qp_defaultDataAsset = nullptr;

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

	Super::Deinitialize();
}

UQPData* UQPGIM_BaseData::QP_GetGameBaseData()
{
	return qp_gameBaseData;
}
UQPData* UQPGIM_BaseData::QP_GetDefaultSetting() {
	return qp_gameBaseData->QP_GetUQPData("QP_GetDefaultSetting");
}
void UQPGIM_BaseData::QP_InitDefaultSetting() {
	qp_defaultDataAsset = LoadObject<UQPDS_DataAsset>(nullptr, TEXT("/Script/QipaWorldUEPlugin.QPDS_DataAsset'/Game/QipaWorld3D/DataAsset/QP_DefaultSetting.QP_DefaultSetting'"));
	if (!qp_defaultDataAsset) {
		qp_defaultDataAsset = LoadObject<UQPDS_DataAsset>(nullptr, TEXT("/Script/QipaWorldUEPlugin.QPDS_DataAsset'/QipaWorldUEPlugin/DataAsset/QP_DefaultSetting.QP_DefaultSetting'"));
	}
	UQPData* qpData = QP_GetDefaultSetting();
	qpData->QP_AddFString("QP_DefaultStartMap", qp_defaultDataAsset->QP_DefaultStartMap);
	qpData->QP_AddFString("QP_DefaultLoadingMap", qp_defaultDataAsset->QP_DefaultLoadingMap);
	qpData->QP_AddFString("QP_DefaultMainUserInterfacePath", qp_defaultDataAsset->QP_DefaultMainUserInterfacePath);
	qpData->QP_AddFString("QP_DefaultCharacterDataPath", qp_defaultDataAsset->QP_DefaultCharacterDataPath);
	qpData->QP_AddFString("QP_DefaultUserInterfaceActionKey", qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey);
	qpData->QP_Addbool("QP_UserInterfaceAutoPop", qp_defaultDataAsset->QP_UserInterfaceAutoPop);
	UQPData* qpuuid = qpData->QP_GetUQPData("QPUUID");
	for (auto uuid : qp_defaultDataAsset->QP_UUID) {
		qpuuid->QP_Addint32(uuid.Key, uuid.Value);
	}
	
}
int32 UQPGIM_BaseData::QP_GetUUID(FString& key) {
	return QP_GetDefaultSetting()->QP_GetUQPData("QPUUID")->QP_Getint32(key);
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




