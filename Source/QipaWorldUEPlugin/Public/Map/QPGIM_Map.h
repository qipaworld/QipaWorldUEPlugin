// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Map.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Map : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Map* QP_UQPGIM_Map;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/** 是否加载完成*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadMap = false;

	/** 子地图是否加载完成*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadSubMap = false;

	/** 这个是准备打开的地图名字*/
	FString qp_readyOpenMapName;

	FString qp_loadingMapName;

	/**子地图加载的action*/
	FLatentActionInfo qp_actionInfo;

	/** 加载新地图，并且保持原来的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation);

	/** 直接切换地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenMap(const FString MapName);

	/** 切换地图的时候加个进度条*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadingAndOpenMap(const FString MapName);
	/** 打开准备加载的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenReadyMap();


	/** 加载子地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadSubMap(const FString MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();


private:
	

};
