// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "World/QPWorldData.h"

#include "QPGIM_Map.generated.h"

/**
 * 地图管理类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Map : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Map* qp_staticObject;
	virtual void QP_InitStaticObject();

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	class UQPData* qp_mapData;
	/** 是否加载完成*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	bool qp_isLoadMap = false;

	/** 子地图是否加载完成*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	bool qp_isLoadSubMap = false;

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	UQPWorldData* qp_worldBaseData = nullptr;
	/** 这个是准备打开的地图名字*/
	FName qp_readyOpenMapName;
	/**带进度条地图的名字*/
	//FString qp_loadingMapName;

	/**子地图加载的action*/
	FLatentActionInfo qp_actionInfo;

	/** 加载新地图，并且保持原来的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadMap(const FString& MapName, const FVector& Location, const FRotator& Rotation);

	/** 直接切换地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_OpenMap(FName MapName);

	/** 切换地图的时候加个进度条*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadingAndOpenMap(FName MapName);
	/** 打开准备加载的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_OpenReadyMap();

	/** 获取地图数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	class UQPData* QP_GetMapData();
	/** 加载子地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadSubMap(FName MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	UQPWorldData* QP_GetMapWorldData();
private:
	

};
