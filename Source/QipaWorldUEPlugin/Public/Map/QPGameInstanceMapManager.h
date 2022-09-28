// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGameInstanceMapManager.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGameInstanceMapManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGameInstanceMapManager* QP_UQPGameInstanceMapManager;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/** 独立加入的子关卡是否加载完成*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadMap = false;

	/** 独立加入的子关卡是否加载完成*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadSubMap = false;

	/** 即将加载的level的名字。*/
	FString qp_readyOpenMapName;

	FString qp_loadingMapName;

	/**加载成功后的回调*/
	FLatentActionInfo qp_actionInfo;

	/** 不卸载现在的level，直接加载新的*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation);

	/** 这个直接切换地图。*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenMap(const FString MapName);

	/** 这个会加载loading场景，之后在切换地图。*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadingAndOpenMap(const FString MapName);
	/** 设置了qp_readyOpenMapName后，可以用这个切换地图。*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenReadyMap();


	/** 加载子地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadSubMap(const FString MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();
private:
	

};
