// QIPAWORLD


#include "Data/QPGIM_PlayerData.h"




#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
#include "Data/QPGIM_BaseData.h"
//#include <MoviePlayer/Public/MoviePlayer.h>
//#include "Data/QPData.h"


UQPGIM_PlayerData* UQPGIM_PlayerData::qp_staticObject = nullptr;


bool UQPGIM_PlayerData::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_PlayerData::Initialize(FSubsystemCollectionBase& Collection)
{
	//UE_LOG(LogTemp, Warning, TEXT("UQPGIM_PlayerData::Initialize______ 1"));

	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());

	QP_InitStaticObject();
	QP_LoadLocalData();
	//UE_LOG(LogTemp, Warning, TEXT("UQPGIM_PlayerData::Initialize______ 2"));

	//
	/*qp_actionInfo.CallbackTarget = this;
	qp_actionInfo.ExecutionFunction = "QP_LoadMapEnd";

	qp_actionInfo.UUID = UQPGIM_BaseData::qp_staticObject->QP_GetUUID("qp_loadMap");
	qp_actionInfo.Linkage = 0;*/

	//qp_loadingMapName = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultLoadingMap;
	//qp_loadingMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}
void UQPGIM_PlayerData::QP_InitStaticObject() {
	UQPGIM_PlayerData::qp_staticObject = this;
}
void UQPGIM_PlayerData::Deinitialize()
{
	//UE_LOG(LogTemp, Warning, TEXT("UQPGIM_PlayerData::Deinitialize______ 1"));

	//QP_SaveData();
	Super::Deinitialize();
	qp_staticObject = nullptr;
	//UE_LOG(LogTemp, Warning, TEXT("UQPGIM_PlayerData::Deinitialize______ 2"));

}

void  UQPGIM_PlayerData::QP_LoadLocalData() {
	qp_localPlayerData = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData();
	qp_localPlayerSaveData = qp_localPlayerData->QP_GetUQPData(qp_saveLocalPlayerDataName);
	//qp_localPlayerSaveData->QP_LoadData("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSave");
	//qp_playerSaveData = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_GetUQPData(qp_savePlayerDataName);
	qp_localPlayerSaveData->QP_LoadDataFAES("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSaveA"));
}
void  UQPGIM_PlayerData::QP_SaveLocalData() {
	qp_localPlayerSaveData->QP_SaveDataFAES("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSaveA"));
	//qp_localPlayerSaveData->QP_SaveData("UQPGIM_PlayerDataQP_LoadLocalDataPlayerDataSave");
}


 UQPData* UQPGIM_PlayerData::QP_GetLocalPlayerData() {
	 return qp_localPlayerData;
 }

UQPData* UQPGIM_PlayerData::QP_GetLocalPlayerSaveData(){
	return qp_localPlayerSaveData;
	}