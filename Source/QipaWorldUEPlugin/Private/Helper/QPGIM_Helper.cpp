// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/QPGIM_Helper.h"
#include "Helper/QPSG_Helper.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPGIM_BaseData.h"
#include "Data/QPData.h"

UQPGIM_Helper* UQPGIM_Helper::qp_staticObject = nullptr;


bool UQPGIM_Helper::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Helper::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());
	QP_InitStaticObject();


	//qp_helperSaveData->AddToRoot();
	qp_helperData = UQPGIM_BaseData::qp_staticObject->QP_GetHelperData();
	
	QP_LoadHelperData();
	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}
void UQPGIM_Helper::QP_InitStaticObject() {
	//UQPUtil::QP_LOG("___________________QP_InitStaticObject_______________");
	UQPGIM_Helper::qp_staticObject = this;
}
void UQPGIM_Helper::Deinitialize()
{
	
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();
	Super::Deinitialize();
	qp_staticObject = nullptr;
}


void UQPGIM_Helper::QP_SetHelperName(FName n, EQPHelperType v)
{
	//qp_helperSaveData->qp_helperData.Add(n, "1");
	//qp_helperSaveData->qp_helperName = n;
	qp_helperData->QP_GetUQPData(qp_dataName)->QP_AddFName("nowHelperName", n);
	qp_helperData->QP_GetUQPData(qp_dataName)->QP_AddValue<FName,int8>(n, static_cast<int8>(v), EQPDataValueType::INT8);

	//QP_SaveHelperData();
	//QP_SaveHelperData();
}



FName UQPGIM_Helper::QP_GetHelperName()
{
	return 	qp_helperData->QP_GetUQPData(qp_dataName)->QP_GetFName("nowHelperName");
}

EQPHelperType UQPGIM_Helper::QP_GetHelperNameState(FName n)
{
	
	return  static_cast<EQPHelperType> (qp_helperData->QP_GetUQPData(qp_dataName)->QP_GetValue<FName,int8>(n,EQPDataValueType::INT8));
	
}

void UQPGIM_Helper::QP_SaveHelperData()
{

	qp_helperData -> QP_GetUQPData(qp_dataName)->QP_SaveData(qp_dataName.ToString());

	
}

//void UQPGIM_Helper::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
//{
//
//}

void UQPGIM_Helper::QP_LoadHelperData()
{
	qp_helperData->QP_GetUQPData(qp_dataName)->qp_dataDelegate.AddUObject(this, &UQPGIM_Helper::QP_BindHelperData);
	qp_helperData->QP_GetUQPData(qp_dataName)->QP_LoadData(qp_dataName.ToString());
	//qp_helperSaveData = UQPSaveGame::QP_LoadSaveData<UQPSG_Helper>(qp_SaveSlotName, qp_UserIndex);
}


void UQPGIM_Helper::QP_BindHelperData(UQPData* data)
{
	/*qp_helperNum = qp_helperData->QP_Getint32("helperNum");
	qp_tipNum = qp_helperData->QP_Getint32("tipNum");
	qp_courseNum = qp_helperData->QP_Getint32("courseNum");*/
	QP_SaveHelperData();
}
