// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPGameInstanceDataManager.h"
#include "Data/QPData.h"

UQPGameInstanceDataManager* UQPGameInstanceDataManager::QP_UQPGameInstanceDataManager = nullptr;
//
//void UQPGameInstanceDataManager::QP_Init()
//{
//	qp_gameQPdataBase = NewObject<UQPData>();
//}


UQPData* UQPGameInstanceDataManager::QP_AddQPData(FString key, UQPData* data)
{
	return qp_gameQPdataBase->QP_AddUQPData(key,data);
}

UQPData* UQPGameInstanceDataManager::QP_GetQPData(FString key)
{
	return qp_gameQPdataBase->QP_GetUQPData(key);
}

void UQPGameInstanceDataManager::QP_RemoveQPData(FString key)
{
	qp_gameQPdataBase->QP_RemoveUQPData(key);
}

void UQPGameInstanceDataManager::QP_AddBroadcastUQPData(UQPData* data)
{
	qp_tempBroadcastArray.Add(data);
}

void UQPGameInstanceDataManager::QP_RemoveBroadcastUQPData(UQPData* data)
{
	qp_tempBroadcastArray.Remove(data);
	qp_broadcastArray.Remove(data);

}

bool UQPGameInstanceDataManager::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGameInstanceDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	QP_UQPGameInstanceDataManager = this;
	qp_gameQPdataBase = NewObject<UQPData>();
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());
}

void UQPGameInstanceDataManager::Deinitialize()
{
	Super::Deinitialize();
}

void UQPGameInstanceDataManager::Tick(float DeltaTime)
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

bool UQPGameInstanceDataManager::IsTickable() const
{
	return !IsTemplate();
}

TStatId UQPGameInstanceDataManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UQPGameInstanceDataManager, STATGROUP_Tickables);
}
