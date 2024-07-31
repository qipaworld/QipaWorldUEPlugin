// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "list"
#include "map"
#include "string"
#include "vector"
#include "QPData.generated.h"

//class UQPGameInstanceDataManager;
class UQPData;
DECLARE_MULTICAST_DELEGATE_OneParam(QP_DataDelegate, UQPData*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQP_DataDynamicDelegate, UQPData*,QPData);

using std::string;
using std::list;
using std::vector;
//using std::string;
/***
* auto add type
* if have *  is a ptr
*/
#define QP_ADD_TYPE(type,...) TMap<FString, type __VA_ARGS__ > qp_##type##Map;

#define QP_ADD_TYPE_CPP_TMap(type,...) TMap<FString, type __VA_ARGS__ > qp_##type##Map;\
void QP_Add##type##(FString , type , bool sync = false);\
void QP_Remove##type##(FString, bool sync = false);\
type QP_Get##type##(FString key);

#define QP_ADD_TYPE_CPP(type,type2,...) std::map<string, type<type2 __VA_ARGS__>*> qp_##type2##type##Map; \
void QP_Add##type2##type##Map(string, type2 __VA_ARGS__, bool sync = false); \
void QP_Remove##type2##type##Map(string,bool sync = false);\
type<type2 __VA_ARGS__>* QP_Get##type2##type##Map(string key);

#define QP_ADD_TYPE_CPP_QPDATA(type,type2,...) std::map<string, type<type2 __VA_ARGS__>*> qp_##type2##type##Map; \
void QP_Add##type2##type##Map(string, bool sync = false); \
void QP_Remove##type2##type##Map(string,bool sync = false);\
type<type2 __VA_ARGS__>* QP_Get##type2##type##Map(string key);

//UENUM(BlueprintType,Category = "QipaWorld|Data")
//enum class EQPDataChangeType :uint8
//{
//	INIT,
//	ADD,
//	CHANGE,
//	REMOVE
//};

//USTRUCT(BlueprintType, Category = "QipaWorld|Data")
//struct FChangeConfig
//{
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Data")
//	EQPDataChangeType qp_changeType;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Data")
//	FString qp_valueType;
//};
/**
 * 数据类，自动发送改动消息。----
 */
UCLASS(Blueprintable,Category = "QipaWorld|Data")

class QIPAWORLDUEPLUGIN_API UQPData : public UObject
{
	GENERATED_BODY()
private:
	QP_ADD_TYPE(UQPData, *)
		QP_ADD_TYPE(UObject, *)
		QP_ADD_TYPE(int32)
		
		QP_ADD_TYPE(float)
		QP_ADD_TYPE(bool)
		QP_ADD_TYPE(FString)
		QP_ADD_TYPE(FText)

		
public:

		QP_ADD_TYPE_CPP_TMap(int8)
		QP_ADD_TYPE_CPP_TMap(int16)
		QP_ADD_TYPE_CPP_TMap(int64)
		QP_ADD_TYPE_CPP_TMap(uint8)
		QP_ADD_TYPE_CPP_TMap(uint16)
		QP_ADD_TYPE_CPP_TMap(uint64)
			QP_ADD_TYPE_CPP_TMap(uint32)
			QP_ADD_TYPE_CPP_TMap(double)


	/** 这个是C++用的代理，---
	 *把你监听这个数据的方法绑定上，数据改变时会自动调用-----
	 *数据内容包括是否是初始化，更改的内容的key，以及数据本身。----
	 */
	QP_DataDelegate qp_dataDelegate;
	/** 这个是蓝图中用的代理，因为速度很慢，所以不推荐C++中使用----
	 *把你监听这个数据的方法绑定上，数据改变时会自动调用----
	 *数据内容包括是否是初始化，更改的内容的key，以及数据本身。----
	 */
	UPROPERTY(BlueprintAssignable, Category = "QipaWorld|QPData")
	FQP_DataDynamicDelegate qp_dataDynamicDelegate;

	FString qp_dataName = "No settings";
	
	/**
	* 里面存放了改变的key，改变类型，----
	* 接收事件的时候可以根据这个判断哪个值发生了变化----
	*/
	TMap<FString,FString > qp_changeMap;

	void QP_Init(FString name);
	
	

	
//protected:
	//发送事件----
	void QP_DelegateBroadcast();
	//发送事件----
	void QP_DynamicDelegateBroadcast();
	// 发送所有事件----
	void QP_BroadcastAll();

	//UQPGameInstanceDataManager* QP_GetDataManager();
	//把事件添加到管理器，下一帧发送----
	void QP_AddBroadcastToDataManager();
	//把事件添加到管理器，下一帧发送----
	void QP_RemoveBroadcastToDataManager();
	//如果需要立刻发送，则立刻发送事件。----
	void QP_needSyncBroadcast(bool sync);



	/**这个千万不要轻易调用，----
	*你直接get，没有会自动帮你创建，----
	*你要是用这个，如果之前这个key下如果有个data，会直接被替换！！！----*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	UQPData* QP_AddUQPData(FString key, UQPData* v = nullptr, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_RemoveUQPData(FString key, bool sync = false);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	UQPData* QP_GetUQPData(FString key);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_AddUObject(FString key, UObject* v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Addint32(FString key, int32 v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Addfloat(FString key, float v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Addbool(FString key, bool v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_AddFString(FString key, FString v, bool sync = false);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_AddFText(FString key, FText v, bool sync = false);

	QP_ADD_TYPE_CPP(list, string);
	QP_ADD_TYPE_CPP(list, int8);
	QP_ADD_TYPE_CPP(list, int16);
	QP_ADD_TYPE_CPP(list, int32);
	QP_ADD_TYPE_CPP(list, int64);
	QP_ADD_TYPE_CPP(list, uint8);
	QP_ADD_TYPE_CPP(list, uint16);
	QP_ADD_TYPE_CPP(list, uint32);
	QP_ADD_TYPE_CPP(list, uint64);
	QP_ADD_TYPE_CPP(list, float);
	QP_ADD_TYPE_CPP(list, double);
	QP_ADD_TYPE_CPP(list, FString);
	QP_ADD_TYPE_CPP_QPDATA(list, UQPData,*);
	QP_ADD_TYPE_CPP(vector, string);
	QP_ADD_TYPE_CPP(vector, int8);
	QP_ADD_TYPE_CPP(vector, int16);
	QP_ADD_TYPE_CPP(vector, int32);
	QP_ADD_TYPE_CPP(vector, int64);
	QP_ADD_TYPE_CPP(vector, uint8);
	QP_ADD_TYPE_CPP(vector, uint16);
	QP_ADD_TYPE_CPP(vector, uint32);
	QP_ADD_TYPE_CPP(vector, uint64);
	QP_ADD_TYPE_CPP(vector, float);
	QP_ADD_TYPE_CPP(vector, double);
	QP_ADD_TYPE_CPP(vector, FString);
	QP_ADD_TYPE_CPP_QPDATA(vector, UQPData,*);
	


	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_RemoveUObject(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Removeint32(FString key, bool sync = false);
	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Removefloat(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_Removebool(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_RemoveFString(FString key, bool sync = false);

	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	void QP_RemoveFText(FString key, bool sync = false);


	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	UObject* QP_GetUObject(FString key);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	int32 QP_Getint32(FString key);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	float QP_Getfloat(FString key);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	bool QP_Getbool(FString key);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	FString QP_GetFString(FString key);
	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
	FText QP_GetFText(FString key);
};
