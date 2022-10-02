// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGIM_Data.h"

#include "Data/QPData.h"

UQPGIM_Data* UQPGIM_Data::QP_UQPGIM_Data = nullptr;
//
//void UQPGIM_Data::QP_Init()
//{
//	qp_baseData = NewObject<UQPData>();
//}


UQPData* UQPGIM_Data::QP_AddQPData(FString key, UQPData* data)
{
	return qp_baseData->QP_AddUQPData(key,data);
}

UQPData* UQPGIM_Data::QP_GetQPData(FString key)
{
	return qp_baseData->QP_GetUQPData(key);
}

void UQPGIM_Data::QP_RemoveQPData(FString key)
{
	qp_baseData->QP_RemoveUQPData(key);
}

void UQPGIM_Data::QP_AddBroadcastUQPData(UQPData* data)
{
	qp_tempBroadcastArray.Add(data);
}

void UQPGIM_Data::QP_RemoveBroadcastUQPData(UQPData* data)
{
	qp_tempBroadcastArray.Remove(data);
	qp_broadcastArray.Remove(data);

}

bool UQPGIM_Data::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Data::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	QP_UQPGIM_Data = this;
	qp_baseData = NewObject<UQPData>();
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());
}

void UQPGIM_Data::Deinitialize()
{
	Super::Deinitialize();
}

void UQPGIM_Data::Tick(float DeltaTime)
{
	for (auto* data : qp_broadcastArray)
	{
		data->QP_BroadcastAll();
	}
	for (auto* data : qp_broadcastArray)
	{
		qp_tempBroadcastArray.Remove(data);
	}
	qp_broadcastArray = qp_tempBroadcastArray;
	qp_tempBroadcastArray.Reset();
}

bool UQPGIM_Data::IsTickable() const
{
	return !IsTemplate();
}

TStatId UQPGIM_Data::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UQPGIM_Data, STATGROUP_Tickables);
}