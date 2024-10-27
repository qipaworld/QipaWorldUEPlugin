// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataAsset/QPDS_DataAsset.h"
#include "QPGIM_BaseData.generated.h"

class UQPData;
/**
 * 这个一些基础的游戏数据存放类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_BaseData : public UGameInstanceSubsystem
{
	GENERATED_BODY()
		//FString qp_gameBaseDataName = "qp_gameBaseDataName";
public:
	static UQPGIM_BaseData* qp_staticObject;

	static UQPDS_DataAsset* qp_defaultDataAsset;
	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/**声音数据*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPSound")
		UQPData* qp_gameBaseData;

	/** 获得数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	UQPData* QP_GetGameBaseData();
	/** 获得数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	UQPData* QP_GetDefaultSetting();
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	int32 QP_GetUUID(FString& key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	UQPData* QP_GetPlayerData();
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	UQPData* QP_GetGameStatusData();
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
	//class UQPDS_DataAsset* QP_GetDefaultSettingDataAsset();
	void QP_InitDefaultSetting();

	
};
