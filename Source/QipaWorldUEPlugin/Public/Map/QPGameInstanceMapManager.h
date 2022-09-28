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

	///** 即将加载或者当前level的名字。*/

	//UPROPERTY(BlueprintReadWrite)
	//FString qp_loadMapName;

	/**加载成功后的回调*/
	FLatentActionInfo qp_actionInfo;
	/** 不卸载现在的level，直接加载新的*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation);

	/** 这个会自动跳到loading界面，之后在加载。*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenMap(const FString MapName);

	/** loading蓝图里用的，因为你在ChangeLevel的时候传名字了，所以这里不需要传。*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadSubMap(const FString MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();
private:
	

};
