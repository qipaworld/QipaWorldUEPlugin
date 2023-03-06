// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGIM_BaseData.h"


#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_BaseData* UQPGIM_BaseData::QP_UQPGIM_BaseData = nullptr;


bool UQPGIM_BaseData::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_BaseData::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPGIM_BaseData = this;

	qp_gameBaseData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData(qp_gameBaseDataName);

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
	QP_UQPGIM_BaseData = nullptr;

	Super::Deinitialize();
}

UQPData* UQPGIM_BaseData::QP_GetGameBaseData()
{
	return qp_gameBaseData;
}

