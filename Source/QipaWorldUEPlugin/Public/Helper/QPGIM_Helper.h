// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Helper.generated.h"

class UQPData;
class UQPSG_Helper;


/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Helper : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Helper* QP_UQPGIM_Helper;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

protected:
	FString qp_dataName = TEXT("helperData");
	/**保存设置的文件名字*/
	FString qp_SaveSlotName = TEXT("qp_helperSaveGame");
	/**保存设置的玩家id*/
	uint32 qp_UserIndex = 0;

	
	virtual void QP_LoadHelperData();
	virtual void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	
public:

	
	/**帮助数据*/
	UPROPERTY(BlueprintReadWrite)
	UQPData* qp_helperData;
	
	UPROPERTY(BlueprintReadWrite)
	UQPSG_Helper* qp_helperSaveData;

	/** 设置新的提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Helper")
	void QP_SetHelperName(FString n);

	/** 获得提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Helper")
	FString QP_GetHelperName();
	
	/** 检测提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Helper")
	bool QP_GetHelperNameState(FString n);

	void QP_SaveHelperData();
	
	void QP_BindHelperData(const UQPData* data);
};
