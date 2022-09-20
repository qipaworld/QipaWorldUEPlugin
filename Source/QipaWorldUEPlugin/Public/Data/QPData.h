// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "QPData.generated.h"
class UQPGameInstanceDataManager;
class UQPData;
DECLARE_MULTICAST_DELEGATE_OneParam(QP_DataDelegate,const UQPData*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQP_DataDynamicDelegate,const UQPData*,QPData);

/***
*这个是自动添加属性的宏
* 带*的是指针QP_RemoveBroadcastUQPData
*/
#define QP_ADD_TYPE(type,...) TMap<FString, ##type __VA_ARGS__ > qp_##type##Map;

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
 * 数据类，自动发送改动消息。
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
	QP_ADD_TYPE(double)
	QP_ADD_TYPE(bool)
	QP_ADD_TYPE(FString)

public:
	/** 这个是C++用的代理，
	 *把你监听这个数据的方法绑定上，数据改变时会自动调用
	 *数据内容包括是否是初始化，更改的内容的key，以及数据本身。
	 */
	QP_DataDelegate qp_dataDelegate;
	/** 这个是蓝图中用的代理，因为速度很慢，所以不推荐C++中使用
	 *把你监听这个数据的方法绑定上，数据改变时会自动调用
	 *数据内容包括是否是初始化，更改的内容的key，以及数据本身。
	 */
	UPROPERTY(BlueprintAssignable)
	FQP_DataDynamicDelegate qp_dataDynamicDelegate;

	FString qp_dataName = "No settings";
	
	/**
	* 里面存放了改变的key，改变类型
	*/
	TMap<FString,FString > qp_changeMap;

	void QP_Init(FString name);
	
	

	
//protected:
	void QP_DelegateBroadcast();
	void QP_DynamicDelegateBroadcast();

	void QP_BroadcastAll();

	//UQPGameInstanceDataManager* QP_GetDataManager();
	void QP_AddBroadcastToDataManager();
	void QP_RemoveBroadcastToDataManager();

	void QP_needSyncBroadcast(bool sync);

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	/**蓝图不支持double*/
	double QP_Getdouble(FString key);
	/**蓝图不支持double*/
	void QP_Adddouble(FString key, double v, bool sync = false);

	/**这个千万不要轻易调用，
	*你直接get，没有会自动帮你创建，
	*你要是用这个，如果之前这个key下如果有个data，会直接被替换！！！*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	UQPData* QP_AddUQPData(FString key, UQPData* v = nullptr, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_RemoveUQPData(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	UQPData* QP_GetUQPData(FString key);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_AddUObject(FString key, UObject* v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Addint32(FString key, int32 v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Addfloat(FString key, float v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Addbool(FString key, bool v, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_AddFString(FString key, FString v, bool sync = false);


	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_RemoveUObject(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Removeint32(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Removefloat(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Removedouble(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_Removebool(FString key, bool sync = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	void QP_RemoveFString(FString key, bool sync = false);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	UObject* QP_GetUObject(FString key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	int32 QP_Getint32(FString key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	float QP_Getfloat(FString key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	bool QP_Getbool(FString key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	FString QP_GetFString(FString key);
};
