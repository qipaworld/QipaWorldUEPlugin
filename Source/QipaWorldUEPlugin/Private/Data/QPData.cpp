// Fill out your copyright notice in the Description page of Project Settings.

#define QP_ADD_TYPE_FUN(type,...) void UQPData::QP_Add##type(FString key, ##type __VA_ARGS__  v, bool sync) {\
	qp_##type##Map.Add(key, v); \
	qp_changeMap.Add(key, "change"); \
	QP_needSyncBroadcast(sync); \
}\
type __VA_ARGS__  UQPData::QP_Get##type(FString key) {\
		return qp_##type##Map.FindOrAdd(key); \
	}\
void UQPData::QP_Remove##type(FString key, bool sync) {\
		if (qp_##type##Map.Contains(key)){\
		qp_##type##Map.Remove(key); \
		qp_changeMap.Add(key, "remove"); \
		QP_needSyncBroadcast(sync);} \
		else{UE_LOG(LogTemp, Warning, TEXT("字典里没有找到%s"),*key);}\
		}


#define QP_ADD_TYPE_FUN_CPP(type,type2,...) void UQPData::QP_Add##type2##type##Map(string key, type2 __VA_ARGS__ v, bool sync) {\
if(qp_##type2##type##Map.find(key)==qp_##type2##type##Map.end())	{\
qp_##type2##type##Map[key] = new type<type2 __VA_ARGS__>();\
}\
qp_##type2##type##Map[key]->push_back(v);\
QP_needSyncBroadcast(sync); \
}\
type<type2 __VA_ARGS__>* UQPData::QP_Get##type2##type##Map(string key) {\
		if(qp_##type2##type##Map.find(key)==qp_##type2##type##Map.end())	{\
qp_##type2##type##Map[key] = new type<type2 __VA_ARGS__>();\
}\
return qp_##type2##type##Map[key];\
	}\
void UQPData::QP_Remove##type2##type##Map(string key,bool sync) {\
auto rmv = qp_##type2##type##Map.find(key);\
if (rmv != qp_##type2##type##Map.end()) {\
		delete rmv->second;\
	qp_##type2##type##Map.erase(rmv);\
		qp_changeMap.Add(key.c_str(), "remove"); \
		QP_needSyncBroadcast(sync);}\
		else{\
	FString outS( key.c_str());\
	UE_LOG(LogTemp, Warning, TEXT("字典里没有找到%s"),*outS);\
}\
		}


#include "Data/QPData.h"
#include <Kismet/GameplayStatics.h>
#include "Data/QPGIM_Data.h"

void UQPData::QP_Init(FString name)
{
	qp_dataName = name;
	AddToRoot();
}

void UQPData::QP_DelegateBroadcast()
{
	qp_dataDelegate.Broadcast(this);
}

void UQPData::QP_DynamicDelegateBroadcast()
{
	qp_dataDynamicDelegate.Broadcast(this);
}

void UQPData::QP_BroadcastAll()
{
	QP_DelegateBroadcast();
	QP_DynamicDelegateBroadcast();
	qp_changeMap.Reset();
}

//UQPGIM_Data* UQPData::QP_GetDataManager()
//{
//	if (qp_dataManager == nullptr) {
//		//UQPGameInstance::qp_gameInstance
//		
//		//qp_dataManager = GetWorld()->GetSubsystem<UQPGIM_Data>();
//	}
//	return qp_dataManager;
//}

void UQPData::QP_AddBroadcastToDataManager()
{
	UQPGIM_Data::qp_staticObject->QP_AddBroadcastUQPData(this);
}

void UQPData::QP_RemoveBroadcastToDataManager()
{
	UQPGIM_Data::qp_staticObject->QP_RemoveBroadcastUQPData(this);
}

void UQPData::QP_needSyncBroadcast(bool sync)
{
	if (sync) {
		QP_BroadcastAll(); 
		QP_RemoveBroadcastToDataManager();
	}
	else if (qp_changeMap.Num() == 1) {
		QP_AddBroadcastToDataManager();
	}
}

UQPData* UQPData::QP_AddUQPData(FString key, UQPData* v, bool sync)
{
	if (v == nullptr)
	{
		v = NewObject<UQPData>();
		v->QP_Init(key);
	}
	qp_UQPDataMap.Add(key, v); 
	qp_changeMap.Add(key, "change");
	QP_needSyncBroadcast(sync);
	return v;
}

UQPData* UQPData::QP_GetUQPData(FString key)
{
	
	if (qp_UQPDataMap.Contains(key))
	{
		return qp_UQPDataMap[key];
	}
	return QP_AddUQPData(key);
}

void UQPData::QP_RemoveUQPData(FString key, bool sync)
{
	if (qp_UQPDataMap.Contains(key))
	{
		qp_UQPDataMap[key]->RemoveFromRoot();
		qp_UQPDataMap.Remove(key);
		qp_changeMap.Add(key, "remove");
		QP_needSyncBroadcast(sync);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("字典里没有找到%s"),*key);
	}
}

QP_ADD_TYPE_FUN(UObject, *)
QP_ADD_TYPE_FUN(int32)
QP_ADD_TYPE_FUN(int64)
QP_ADD_TYPE_FUN(float)
QP_ADD_TYPE_FUN(double)
QP_ADD_TYPE_FUN(bool)
QP_ADD_TYPE_FUN(FString)

QP_ADD_TYPE_FUN_CPP(list, string);
QP_ADD_TYPE_FUN_CPP(list, int32);
QP_ADD_TYPE_FUN_CPP(list, int64);
QP_ADD_TYPE_FUN_CPP(list, float);
QP_ADD_TYPE_FUN_CPP(list, double);
QP_ADD_TYPE_FUN_CPP(list, FString);
QP_ADD_TYPE_FUN_CPP(vector, string);
QP_ADD_TYPE_FUN_CPP(vector, int32);
QP_ADD_TYPE_FUN_CPP(vector, int64);
QP_ADD_TYPE_FUN_CPP(vector, float);
QP_ADD_TYPE_FUN_CPP(vector, double);
QP_ADD_TYPE_FUN_CPP(vector, FString);