// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Helper.generated.h"

class UQPData;
class UQPSG_Helper;


/**
 * 教程管理基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Helper : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Helper* qp_staticObject;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

protected:
	/**在数据管理器里的名字*/
	FString qp_dataName = TEXT("UQPGIM_Helper");
	/**保存设置的文件名字*/
	FString qp_SaveSlotName = TEXT("qp_helperSaveGame");
	/**保存设置的玩家id*/
	uint32 qp_UserIndex = 0;

	/**加载数据*/
	virtual void QP_LoadHelperData();
	/**保存数据*/
	virtual void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	
public:

	
	/**帮助数据*/
	UPROPERTY(BlueprintReadWrite)
	UQPData* qp_helperData;
	/**存储数据类*/
	UPROPERTY(BlueprintReadWrite)
	UQPSG_Helper* qp_helperSaveData;

	/** 设置新的提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPHelper")
	void QP_SetHelperName(FString n);

	/** 获得提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPHelper")
	FString QP_GetHelperName();
	
	/** 检测提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPHelper")
	bool QP_GetHelperNameState(FString n);

	void QP_SaveHelperData();
	/**监听帮助数据，如果变了就保存*/
	void QP_BindHelperData(UQPData* data);
};
