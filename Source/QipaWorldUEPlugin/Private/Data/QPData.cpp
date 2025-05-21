// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QPData.h"
#include <Kismet/GameplayStatics.h>
#include "Data/QPGIM_Data.h"

void UQPData::BeginDestroy()
{
	Super::BeginDestroy();

	for (auto v : qp_ValueMap) {
		//for (auto v2 : v.Value) {
			delete v.Value;
		//}
	}
}

//void UQPData::QP_Init()
//{
//	
//}

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
		//for (auto v2 : v.Value) {
			((IQPBaseData*)v.Value)->QP_RestChangeMap();
		//}
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

void UQPData::QP_needSyncBroadcast(EQPDataBroadcastType bType)
{
	switch (bType)
	{
	case EQPDataBroadcastType::DEFAULT: 
	{
		if (!qp_isAddToManager) {
			QP_AddBroadcastToDataManager();
		}
		break;
	}
	case EQPDataBroadcastType::SYNC:
	{
		QP_BroadcastAll();
		QP_RemoveBroadcastToDataManager();
		break;
	}
	case EQPDataBroadcastType::NONE:
		break;
	default:
		break;
	}
	
}
void UQPData::QP_BroadcastNow() {
	QP_BroadcastAll();
	QP_RemoveBroadcastToDataManager();
}
//QP_ADD_TYPE_FUN_QPDATA(const FName&, FName, EQPDataKeyType::FNAME, UQPData)
//QP_ADD_TYPE_FUN_QPDATA(int32,int32, EQPDataKeyType::INT32, UQPDataExI)
//QP_ADD_TYPE_FUN_QPDATA(UObject*,UObject*,EQPDataKeyType::VOID,UQPDataExO)

//-----------------------


//QP_ADD_TYPE_FUN(UObject*, UObject*, const FName&, UObject*, EQPDataKeyType::FNAME, EQPDataValueType::UOBJECT, UObject)
//QP_ADD_TYPE_FUN(int32, int32, const FName&, int32, EQPDataKeyType::FNAME, EQPDataValueType::INT32, int32)
//QP_ADD_TYPE_FUN(float, float, const FName&, float, EQPDataKeyType::FNAME, EQPDataValueType::FLOAT, float)
//QP_ADD_TYPE_FUN(bool, bool, const FName&, bool, EQPDataKeyType::FNAME, EQPDataValueType::BOOL, bool)
//QP_ADD_TYPE_FUN(FString&, const FString&, const FName&, FString, EQPDataKeyType::FNAME, EQPDataValueType::FSTRING, FString)
//QP_ADD_TYPE_FUN(FText&, const FText&, const FName&, FText, EQPDataKeyType::FNAME, EQPDataValueType::FTEXT, FText)
//QP_ADD_TYPE_FUN(FName&, const FName&, const FName&, FName, EQPDataKeyType::FNAME, EQPDataValueType::FNAME, FName)
//QP_ADD_TYPE_FUN(FVector&, const FVector&, const FName&, FVector, EQPDataKeyType::FNAME, EQPDataValueType::FVECTOR, FVector)
////QP_ADD_TYPE_FUN(TArray&, const TArray&, FName, TArray, EQPDataKeyType::FNAME, EQPDataValueType::TARRAY, TArray)
//
//QP_ADD_TYPE_FUN(UObject*, UObject*, UObject*, UObject*, EQPDataKeyType::VOID, EQPDataValueType::UOBJECT, UObjectExO)
//QP_ADD_TYPE_FUN(int32, int32, UObject*, int32, EQPDataKeyType::VOID, EQPDataValueType::INT32, int32ExO)
//QP_ADD_TYPE_FUN(float, float, UObject*, float, EQPDataKeyType::VOID, EQPDataValueType::FLOAT, floatExO)
//QP_ADD_TYPE_FUN(bool, bool, UObject*, bool, EQPDataKeyType::VOID, EQPDataValueType::BOOL, boolExO)
//QP_ADD_TYPE_FUN(FString&, const FString&, UObject*, FString, EQPDataKeyType::VOID, EQPDataValueType::FSTRING, FStringExO)
//QP_ADD_TYPE_FUN(FText&, const FText&, UObject*, FText, EQPDataKeyType::VOID, EQPDataValueType::FTEXT, FTextExO)
//QP_ADD_TYPE_FUN(FName&, const FName&, UObject*, FName, EQPDataKeyType::VOID, EQPDataValueType::FNAME, FNameExO)
//QP_ADD_TYPE_FUN(FVector&, const FVector&, UObject*, FVector, EQPDataKeyType::VOID, EQPDataValueType::FVECTOR, FVectorExO)
////QP_ADD_TYPE_FUN(TArray&, const TArray&, UObject*, TArray, EQPDataKeyType::VOID, EQPDataValueType::TARRAY, TArrayExO)
//
//
//QP_ADD_TYPE_FUN(UObject*, UObject*, int32, UObject*, EQPDataKeyType::INT32, EQPDataValueType::UOBJECT, UObjectExI)
//QP_ADD_TYPE_FUN(int32, int32, int32, int32, EQPDataKeyType::INT32, EQPDataValueType::INT32, int32ExI)
//QP_ADD_TYPE_FUN(float, float, int32, float, EQPDataKeyType::INT32, EQPDataValueType::FLOAT, floatExI)
//QP_ADD_TYPE_FUN(bool, bool, int32, bool, EQPDataKeyType::INT32, EQPDataValueType::BOOL, boolExI)
//QP_ADD_TYPE_FUN(FString&, const FString&, int32, FString, EQPDataKeyType::INT32, EQPDataValueType::FSTRING, FStringExI)
//QP_ADD_TYPE_FUN(FText&, const FText&, int32, FText, EQPDataKeyType::INT32, EQPDataValueType::FTEXT, FTextExI)
//QP_ADD_TYPE_FUN(FName&, const FName&, int32, FName, EQPDataKeyType::INT32, EQPDataValueType::FNAME, FNameExI)
//QP_ADD_TYPE_FUN(FVector&, const FVector&, int32, FVector, EQPDataKeyType::INT32, EQPDataValueType::FVECTOR, FVectorExI)
//QP_ADD_TYPE_FUN(TArray&, const TArray&, int32, TArray, EQPDataKeyType::INT32, EQPDataValueType::TARRAY, FTArrayExI)

//QP_ADD_TYPE_FUN(double, double, int32, double, EQPDataKeyType::INT32, EQPDataValueType::DOUBLE, doubleExI)
//QP_ADD_TYPE_FUN(double, double, UObject*, double, EQPDataKeyType::VOID, EQPDataValueType::DOUBLE, doubleExO)
//QP_ADD_TYPE_FUN(double, double, FName, double, EQPDataKeyType::FNAME, EQPDataValueType::DOUBLE, double)
//
//QP_ADD_TYPE_FUN(int64, int64, int32, int64, EQPDataKeyType::INT32, EQPDataValueType::INT64, int64ExI)
//QP_ADD_TYPE_FUN(int64, int64, UObject*, int64, EQPDataKeyType::VOID, EQPDataValueType::INT64, int64ExO)
//QP_ADD_TYPE_FUN(int64, int64, FName, int64, EQPDataKeyType::FNAME, EQPDataValueType::INT64, int64)


//------------auto generator start

void UQPData::QP_Adddouble(FName  key, double v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , double>(key,v,EQPDataValueType::DOUBLE,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_Containsdouble(FName  key)
{
    return QP_Contains<FName ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::FNAME );
}

double UQPData::QP_Getdouble(FName  key)
{
    return QP_GetValue<FName , double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Removedouble(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_Cleardouble( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,double>(EQPDataValueType::DOUBLE,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AdddoubleExI(int32  key, double v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , double>(key,v,EQPDataValueType::DOUBLE,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsdoubleExI(int32  key)
{
    return QP_Contains<int32 ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::INT32 );
}

double UQPData::QP_GetdoubleExI(int32  key)
{
    return QP_GetValue<int32 , double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemovedoubleExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_CleardoubleExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,double>(EQPDataValueType::DOUBLE,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AdddoubleExO(UObject*  key, double v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , double>(key,v,EQPDataValueType::DOUBLE,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsdoubleExO(UObject*  key)
{
    return QP_Contains<UObject* ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::VOID );
}

double UQPData::QP_GetdoubleExO(UObject*  key)
{
    return QP_GetValue<UObject* , double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemovedoubleExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,double>(key,EQPDataValueType::DOUBLE,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_CleardoubleExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,double>(EQPDataValueType::DOUBLE,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_Addint64(FName  key, int64 v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , int64>(key,v,EQPDataValueType::INT64,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_Containsint64(FName  key)
{
    return QP_Contains<FName ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::FNAME );
}

int64 UQPData::QP_Getint64(FName  key)
{
    return QP_GetValue<FName , int64>(key,EQPDataValueType::INT64,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Removeint64(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_Clearint64( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,int64>(EQPDataValueType::INT64,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_Addint64ExI(int32  key, int64 v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , int64>(key,v,EQPDataValueType::INT64,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_Containsint64ExI(int32  key)
{
    return QP_Contains<int32 ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::INT32 );
}

int64 UQPData::QP_Getint64ExI(int32  key)
{
    return QP_GetValue<int32 , int64>(key,EQPDataValueType::INT64,EQPDataKeyType::INT32 );
}

bool UQPData::QP_Removeint64ExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_Clearint64ExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,int64>(EQPDataValueType::INT64,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_Addint64ExO(UObject*  key, int64 v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , int64>(key,v,EQPDataValueType::INT64,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_Containsint64ExO(UObject*  key)
{
    return QP_Contains<UObject* ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::VOID );
}

int64 UQPData::QP_Getint64ExO(UObject*  key)
{
    return QP_GetValue<UObject* , int64>(key,EQPDataValueType::INT64,EQPDataKeyType::VOID );
}

bool UQPData::QP_Removeint64ExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,int64>(key,EQPDataValueType::INT64,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_Clearint64ExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,int64>(EQPDataValueType::INT64,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddFVector(FName  key, const FVector& v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , FVector>(key,v,EQPDataValueType::FVECTOR,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsFVector(FName  key)
{
    return QP_Contains<FName ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::FNAME );
}

FVector& UQPData::QP_GetFVector(FName  key)
{
    return QP_GetValue<FName , FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveFVector(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearFVector( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,FVector>(EQPDataValueType::FVECTOR,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddFVectorExI(int32  key, const FVector& v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , FVector>(key,v,EQPDataValueType::FVECTOR,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsFVectorExI(int32  key)
{
    return QP_Contains<int32 ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::INT32 );
}

FVector& UQPData::QP_GetFVectorExI(int32  key)
{
    return QP_GetValue<int32 , FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveFVectorExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearFVectorExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,FVector>(EQPDataValueType::FVECTOR,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddFVectorExO(UObject*  key, const FVector& v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , FVector>(key,v,EQPDataValueType::FVECTOR,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsFVectorExO(UObject*  key)
{
    return QP_Contains<UObject* ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::VOID );
}

FVector& UQPData::QP_GetFVectorExO(UObject*  key)
{
    return QP_GetValue<UObject* , FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveFVectorExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,FVector>(key,EQPDataValueType::FVECTOR,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearFVectorExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,FVector>(EQPDataValueType::FVECTOR,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddFName(FName  key, const FName& v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , FName>(key,v,EQPDataValueType::FNAME,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsFName(FName  key)
{
    return QP_Contains<FName ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::FNAME );
}

FName& UQPData::QP_GetFName(FName  key)
{
    return QP_GetValue<FName , FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveFName(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearFName( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,FName>(EQPDataValueType::FNAME,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddFNameExI(int32  key, const FName& v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , FName>(key,v,EQPDataValueType::FNAME,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsFNameExI(int32  key)
{
    return QP_Contains<int32 ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::INT32 );
}

FName& UQPData::QP_GetFNameExI(int32  key)
{
    return QP_GetValue<int32 , FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveFNameExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearFNameExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,FName>(EQPDataValueType::FNAME,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddFNameExO(UObject*  key, const FName& v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , FName>(key,v,EQPDataValueType::FNAME,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsFNameExO(UObject*  key)
{
    return QP_Contains<UObject* ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::VOID );
}

FName& UQPData::QP_GetFNameExO(UObject*  key)
{
    return QP_GetValue<UObject* , FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveFNameExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,FName>(key,EQPDataValueType::FNAME,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearFNameExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,FName>(EQPDataValueType::FNAME,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddFText(FName  key, const FText& v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , FText>(key,v,EQPDataValueType::FTEXT,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsFText(FName  key)
{
    return QP_Contains<FName ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::FNAME );
}

FText& UQPData::QP_GetFText(FName  key)
{
    return QP_GetValue<FName , FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveFText(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearFText( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,FText>(EQPDataValueType::FTEXT,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddFTextExI(int32  key, const FText& v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , FText>(key,v,EQPDataValueType::FTEXT,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsFTextExI(int32  key)
{
    return QP_Contains<int32 ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::INT32 );
}

FText& UQPData::QP_GetFTextExI(int32  key)
{
    return QP_GetValue<int32 , FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveFTextExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearFTextExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,FText>(EQPDataValueType::FTEXT,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddFTextExO(UObject*  key, const FText& v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , FText>(key,v,EQPDataValueType::FTEXT,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsFTextExO(UObject*  key)
{
    return QP_Contains<UObject* ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::VOID );
}

FText& UQPData::QP_GetFTextExO(UObject*  key)
{
    return QP_GetValue<UObject* , FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveFTextExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,FText>(key,EQPDataValueType::FTEXT,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearFTextExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,FText>(EQPDataValueType::FTEXT,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddFString(FName  key, const FString& v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , FString>(key,v,EQPDataValueType::FSTRING,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsFString(FName  key)
{
    return QP_Contains<FName ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::FNAME );
}

FString& UQPData::QP_GetFString(FName  key)
{
    return QP_GetValue<FName , FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveFString(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearFString( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,FString>(EQPDataValueType::FSTRING,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddFStringExI(int32  key, const FString& v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , FString>(key,v,EQPDataValueType::FSTRING,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsFStringExI(int32  key)
{
    return QP_Contains<int32 ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::INT32 );
}

FString& UQPData::QP_GetFStringExI(int32  key)
{
    return QP_GetValue<int32 , FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveFStringExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearFStringExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,FString>(EQPDataValueType::FSTRING,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddFStringExO(UObject*  key, const FString& v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , FString>(key,v,EQPDataValueType::FSTRING,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsFStringExO(UObject*  key)
{
    return QP_Contains<UObject* ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::VOID );
}

FString& UQPData::QP_GetFStringExO(UObject*  key)
{
    return QP_GetValue<UObject* , FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveFStringExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,FString>(key,EQPDataValueType::FSTRING,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearFStringExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,FString>(EQPDataValueType::FSTRING,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_Addbool(FName  key, bool v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , bool>(key,v,EQPDataValueType::BOOL,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_Containsbool(FName  key)
{
    return QP_Contains<FName ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Getbool(FName  key)
{
    return QP_GetValue<FName , bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Removebool(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_Clearbool( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,bool>(EQPDataValueType::BOOL,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddboolExI(int32  key, bool v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , bool>(key,v,EQPDataValueType::BOOL,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsboolExI(int32  key)
{
    return QP_Contains<int32 ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::INT32 );
}

bool UQPData::QP_GetboolExI(int32  key)
{
    return QP_GetValue<int32 , bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveboolExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearboolExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,bool>(EQPDataValueType::BOOL,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddboolExO(UObject*  key, bool v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , bool>(key,v,EQPDataValueType::BOOL,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsboolExO(UObject*  key)
{
    return QP_Contains<UObject* ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::VOID );
}

bool UQPData::QP_GetboolExO(UObject*  key)
{
    return QP_GetValue<UObject* , bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveboolExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,bool>(key,EQPDataValueType::BOOL,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearboolExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,bool>(EQPDataValueType::BOOL,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_Addfloat(FName  key, float v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , float>(key,v,EQPDataValueType::FLOAT,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_Containsfloat(FName  key)
{
    return QP_Contains<FName ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::FNAME );
}

float UQPData::QP_Getfloat(FName  key)
{
    return QP_GetValue<FName , float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Removefloat(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_Clearfloat( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,float>(EQPDataValueType::FLOAT,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddfloatExI(int32  key, float v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , float>(key,v,EQPDataValueType::FLOAT,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsfloatExI(int32  key)
{
    return QP_Contains<int32 ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::INT32 );
}

float UQPData::QP_GetfloatExI(int32  key)
{
    return QP_GetValue<int32 , float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemovefloatExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearfloatExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,float>(EQPDataValueType::FLOAT,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddfloatExO(UObject*  key, float v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , float>(key,v,EQPDataValueType::FLOAT,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsfloatExO(UObject*  key)
{
    return QP_Contains<UObject* ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::VOID );
}

float UQPData::QP_GetfloatExO(UObject*  key)
{
    return QP_GetValue<UObject* , float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemovefloatExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,float>(key,EQPDataValueType::FLOAT,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearfloatExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,float>(EQPDataValueType::FLOAT,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_Addint32(FName  key, int32 v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , int32>(key,v,EQPDataValueType::INT32,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_Containsint32(FName  key)
{
    return QP_Contains<FName ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::FNAME );
}

int32 UQPData::QP_Getint32(FName  key)
{
    return QP_GetValue<FName , int32>(key,EQPDataValueType::INT32,EQPDataKeyType::FNAME );
}

bool UQPData::QP_Removeint32(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_Clearint32( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,int32>(EQPDataValueType::INT32,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_Addint32ExI(int32  key, int32 v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , int32>(key,v,EQPDataValueType::INT32,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_Containsint32ExI(int32  key)
{
    return QP_Contains<int32 ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::INT32 );
}

int32 UQPData::QP_Getint32ExI(int32  key)
{
    return QP_GetValue<int32 , int32>(key,EQPDataValueType::INT32,EQPDataKeyType::INT32 );
}

bool UQPData::QP_Removeint32ExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_Clearint32ExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,int32>(EQPDataValueType::INT32,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_Addint32ExO(UObject*  key, int32 v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , int32>(key,v,EQPDataValueType::INT32,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_Containsint32ExO(UObject*  key)
{
    return QP_Contains<UObject* ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::VOID );
}

int32 UQPData::QP_Getint32ExO(UObject*  key)
{
    return QP_GetValue<UObject* , int32>(key,EQPDataValueType::INT32,EQPDataKeyType::VOID );
}

bool UQPData::QP_Removeint32ExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,int32>(key,EQPDataValueType::INT32,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_Clearint32ExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,int32>(EQPDataValueType::INT32,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddUObject(FName  key, UObject* v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , UObject*>(key,v,EQPDataValueType::UOBJECT,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsUObject(FName  key)
{
    return QP_Contains<FName ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::FNAME );
}

UObject* UQPData::QP_GetUObject(FName  key)
{
    return QP_GetValue<FName , UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveUObject(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearUObject( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,UObject*>(EQPDataValueType::UOBJECT,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddUObjectExI(int32  key, UObject* v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , UObject*>(key,v,EQPDataValueType::UOBJECT,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsUObjectExI(int32  key)
{
    return QP_Contains<int32 ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::INT32 );
}

UObject* UQPData::QP_GetUObjectExI(int32  key)
{
    return QP_GetValue<int32 , UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveUObjectExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearUObjectExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,UObject*>(EQPDataValueType::UOBJECT,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddUObjectExO(UObject*  key, UObject* v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , UObject*>(key,v,EQPDataValueType::UOBJECT,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsUObjectExO(UObject*  key)
{
    return QP_Contains<UObject* ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::VOID );
}

UObject* UQPData::QP_GetUObjectExO(UObject*  key)
{
    return QP_GetValue<UObject* , UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveUObjectExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,UObject*>(key,EQPDataValueType::UOBJECT,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearUObjectExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,UObject*>(EQPDataValueType::UOBJECT,EQPDataKeyType::VOID ,bType);
}


void UQPData::QP_AddUQPData(FName  key, UQPData* v, EQPDataBroadcastType bType)
{
    QP_AddValue<FName , UQPData*>(key,v,EQPDataValueType::UQPDATA,EQPDataKeyType::FNAME ,bType);
}

bool UQPData::QP_ContainsUQPData(FName  key)
{
    return QP_Contains<FName ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::FNAME );
}

UQPData* UQPData::QP_GetUQPData(FName  key)
{
    return QP_GetValue<FName , UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::FNAME );
}

bool UQPData::QP_RemoveUQPData(FName  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<FName ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::FNAME ,bType);
}

void UQPData::QP_ClearUQPData( EQPDataBroadcastType bType)
{
    QP_ClearValue<FName ,UQPData*>(EQPDataValueType::UQPDATA,EQPDataKeyType::FNAME ,bType);
}


void UQPData::QP_AddUQPDataExI(int32  key, UQPData* v, EQPDataBroadcastType bType)
{
    QP_AddValue<int32 , UQPData*>(key,v,EQPDataValueType::UQPDATA,EQPDataKeyType::INT32 ,bType);
}

bool UQPData::QP_ContainsUQPDataExI(int32  key)
{
    return QP_Contains<int32 ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::INT32 );
}

UQPData* UQPData::QP_GetUQPDataExI(int32  key)
{
    return QP_GetValue<int32 , UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::INT32 );
}

bool UQPData::QP_RemoveUQPDataExI(int32  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<int32 ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::INT32 ,bType);
}

void UQPData::QP_ClearUQPDataExI( EQPDataBroadcastType bType)
{
    QP_ClearValue<int32 ,UQPData*>(EQPDataValueType::UQPDATA,EQPDataKeyType::INT32 ,bType);
}


void UQPData::QP_AddUQPDataExO(UObject*  key, UQPData* v, EQPDataBroadcastType bType)
{
    QP_AddValue<UObject* , UQPData*>(key,v,EQPDataValueType::UQPDATA,EQPDataKeyType::VOID ,bType);
}

bool UQPData::QP_ContainsUQPDataExO(UObject*  key)
{
    return QP_Contains<UObject* ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::VOID );
}

UQPData* UQPData::QP_GetUQPDataExO(UObject*  key)
{
    return QP_GetValue<UObject* , UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::VOID );
}

bool UQPData::QP_RemoveUQPDataExO(UObject*  key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<UObject* ,UQPData*>(key,EQPDataValueType::UQPDATA,EQPDataKeyType::VOID ,bType);
}

void UQPData::QP_ClearUQPDataExO( EQPDataBroadcastType bType)
{
    QP_ClearValue<UObject* ,UQPData*>(EQPDataValueType::UQPDATA,EQPDataKeyType::VOID ,bType);
}


//------------auto generator end



