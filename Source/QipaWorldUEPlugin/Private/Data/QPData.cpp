// Fill out your copyright notice in the Description page of Project Settings.



#define QP_ADD_TYPE_FUN(funType,funValue,typeKey,typeValue,typeEnumK,typeEnumV,NameEx) void UQPData::QP_Add##NameEx (typeKey key, funValue v, bool sync)\
{\
	if (!qp_ValueMap.FindOrAdd(typeEnumK).Contains(typeEnumV)) {\
		qp_ValueMap[typeEnumK].Emplace(typeEnumV, new QPBaseData<typeKey, typeValue>(typeEnumV,typeEnumK));\
	}\
	((QPBaseData<typeKey, typeValue>*)qp_ValueMap[typeEnumK][typeEnumV])->QP_AddValue(key, v);\
	QP_needSyncBroadcast(sync);\
}\
funType UQPData::QP_Get##NameEx (typeKey key)\
{\
	if (!qp_ValueMap.FindOrAdd(typeEnumK).Contains(typeEnumV)) {\
		 qp_ValueMap[typeEnumK].Emplace(typeEnumV, new QPBaseData<typeKey, typeValue>(typeEnumV,typeEnumK));\
	}\
	return ((QPBaseData<typeKey, typeValue>*)qp_ValueMap[typeEnumK][typeEnumV])->qp_ValueMap.FindOrAdd(key);\
}\
bool UQPData::QP_Contains##NameEx (typeKey key) {\
	return QP_Contains<typeKey,typeValue>(key,typeEnumV,typeEnumK);\
}\
void UQPData::QP_Remove##NameEx (typeKey key, bool sync)\
{\
	QP_RemoveValue<typeKey,typeValue>(key,typeEnumV,typeEnumK,sync);\
}\
void UQPData::QP_Clear##NameEx ( bool sync) {\
	QP_ClearValue<typeKey,typeValue>(typeEnumV,typeEnumK,sync);\
}

#define QP_ADD_TYPE_FUN_QPDATA(typeKey,typeEnumK,NameEx) void UQPData::QP_Add##NameEx (typeKey key, UQPData* v, bool sync)\
{\
	QP_AddValue<typeKey, UQPData*>(key,v,EQPDataValueType::UQPDATA,typeEnumK,sync);\
}\
UQPData* UQPData::QP_Get##NameEx (typeKey key)\
{\
	return QP_GetValue<typeKey, UQPData*>(key,EQPDataValueType::UQPDATA,typeEnumK);\
}\
bool UQPData::QP_Contains##NameEx (typeKey key) {\
return QP_Contains<typeKey, UQPData*>(key,EQPDataValueType::UQPDATA,typeEnumK);\
}\
bool UQPData::QP_Remove##NameEx (typeKey key, bool sync)\
{\
	return QP_RemoveValue<typeKey, UQPData*>(key,EQPDataValueType::UQPDATA,typeEnumK,sync);\
}\
void UQPData::QP_Clear##NameEx ( bool sync) {\
	QP_ClearValue<typeKey, UQPData*>(EQPDataValueType::UQPDATA,typeEnumK,sync);\
}

#include "Data/QPData.h"
#include <Kismet/GameplayStatics.h>
#include "Data/QPGIM_Data.h"


void UQPData::BeginDestroy()
{
	Super::BeginDestroy();

	for (auto v : qp_ValueMap) {
		for (auto v2 : v.Value) {
			delete v2.Value;
		}
	}
}

void UQPData::QP_Init()
{
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
	for (auto v : qp_ValueMap) {
		for (auto v2 : v.Value) {
			((IQPBaseData*)v2.Value)->QP_RestChangeMap();
		}
	}
	qp_isAddToManager = false;
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
	qp_isAddToManager = true;
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
	else if (!qp_isAddToManager) {
		QP_AddBroadcastToDataManager();
	}
}
void UQPData::QP_BroadcastNow() {
	QP_BroadcastAll();
	QP_RemoveBroadcastToDataManager();
}
QP_ADD_TYPE_FUN_QPDATA(FName, EQPDataKeyType::FNAME, UQPData)
QP_ADD_TYPE_FUN_QPDATA(int32, EQPDataKeyType::INT32, UQPDataExI)
QP_ADD_TYPE_FUN_QPDATA(UObject*,EQPDataKeyType::VOID,UQPDataExO)

//-----------------------


QP_ADD_TYPE_FUN(UObject*, UObject*, FName, UObject*, EQPDataKeyType::FNAME, EQPDataValueType::UOBJECT, UObject)
QP_ADD_TYPE_FUN(int32, int32, FName, int32, EQPDataKeyType::FNAME, EQPDataValueType::INT32, int32)
QP_ADD_TYPE_FUN(float, float, FName, float, EQPDataKeyType::FNAME, EQPDataValueType::FLOAT, float)
QP_ADD_TYPE_FUN(bool, bool, FName, bool, EQPDataKeyType::FNAME, EQPDataValueType::BOOL, bool)
QP_ADD_TYPE_FUN(FString&, const FString&, FName, FString, EQPDataKeyType::FNAME, EQPDataValueType::FSTRING, FString)
QP_ADD_TYPE_FUN(FText&, const FText&, FName, FText, EQPDataKeyType::FNAME, EQPDataValueType::FTEXT, FText)
QP_ADD_TYPE_FUN(FName, FName, FName, FName, EQPDataKeyType::FNAME, EQPDataValueType::FNAME, FName)
QP_ADD_TYPE_FUN(FVector&, const FVector&, FName, FVector, EQPDataKeyType::FNAME, EQPDataValueType::FVECTOR, FVector)
//QP_ADD_TYPE_FUN(TArray&, const TArray&, FName, TArray, EQPDataKeyType::FNAME, EQPDataValueType::TARRAY, TArray)

QP_ADD_TYPE_FUN(UObject*, UObject*, UObject*, UObject*, EQPDataKeyType::VOID, EQPDataValueType::UOBJECT, UObjectExO)
QP_ADD_TYPE_FUN(int32, int32, UObject*, int32, EQPDataKeyType::VOID, EQPDataValueType::INT32, int32ExO)
QP_ADD_TYPE_FUN(float, float, UObject*, float, EQPDataKeyType::VOID, EQPDataValueType::FLOAT, floatExO)
QP_ADD_TYPE_FUN(bool, bool, UObject*, bool, EQPDataKeyType::VOID, EQPDataValueType::BOOL, boolExO)
QP_ADD_TYPE_FUN(FString&, const FString&, UObject*, FString, EQPDataKeyType::VOID, EQPDataValueType::FSTRING, FStringExO)
QP_ADD_TYPE_FUN(FText&, const FText&, UObject*, FText, EQPDataKeyType::VOID, EQPDataValueType::FTEXT, FTextExO)
QP_ADD_TYPE_FUN(FName, FName, UObject*, FName, EQPDataKeyType::VOID, EQPDataValueType::FNAME, FNameExO)
QP_ADD_TYPE_FUN(FVector&, const FVector&, UObject*, FVector, EQPDataKeyType::VOID, EQPDataValueType::FVECTOR, FVectorExO)
//QP_ADD_TYPE_FUN(TArray&, const TArray&, UObject*, TArray, EQPDataKeyType::VOID, EQPDataValueType::TARRAY, TArrayExO)


QP_ADD_TYPE_FUN(UObject*, UObject*, int32, UObject*, EQPDataKeyType::INT32, EQPDataValueType::UOBJECT, UObjectExI)
QP_ADD_TYPE_FUN(int32, int32, int32, int32, EQPDataKeyType::INT32, EQPDataValueType::INT32, int32ExI)
QP_ADD_TYPE_FUN(float, float, int32, float, EQPDataKeyType::INT32, EQPDataValueType::FLOAT, floatExI)
QP_ADD_TYPE_FUN(bool, bool, int32, bool, EQPDataKeyType::INT32, EQPDataValueType::BOOL, boolExI)
QP_ADD_TYPE_FUN(FString&, const FString&, int32, FString, EQPDataKeyType::INT32, EQPDataValueType::FSTRING, FStringExI)
QP_ADD_TYPE_FUN(FText&, const FText&, int32, FText, EQPDataKeyType::INT32, EQPDataValueType::FTEXT, FTextExI)
QP_ADD_TYPE_FUN(FName, FName, int32, FName, EQPDataKeyType::INT32, EQPDataValueType::FNAME, FNameExI)
QP_ADD_TYPE_FUN(FVector&, const FVector&, int32, FVector, EQPDataKeyType::INT32, EQPDataValueType::FVECTOR, FVectorExI)
//QP_ADD_TYPE_FUN(TArray&, const TArray&, int32, TArray, EQPDataKeyType::INT32, EQPDataValueType::TARRAY, FTArrayExI)

QP_ADD_TYPE_FUN(double, double, int32, double, EQPDataKeyType::INT32, EQPDataValueType::DOUBLE, doubleExI)
QP_ADD_TYPE_FUN(double, double, UObject*, double, EQPDataKeyType::VOID, EQPDataValueType::DOUBLE, doubleExO)
QP_ADD_TYPE_FUN(double, double, FName, double, EQPDataKeyType::FNAME, EQPDataValueType::DOUBLE, double)

QP_ADD_TYPE_FUN(int64, int64, int32, int64, EQPDataKeyType::INT32, EQPDataValueType::INT64, int64ExI)
QP_ADD_TYPE_FUN(int64, int64, UObject*, int64, EQPDataKeyType::VOID, EQPDataValueType::INT64, int64ExO)
QP_ADD_TYPE_FUN(int64, int64, FName, int64, EQPDataKeyType::FNAME, EQPDataValueType::INT64, int64)







