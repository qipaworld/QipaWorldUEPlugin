// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Helper.generated.h"

class UQPData;

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

public:

	/**帮助数据*/
	UPROPERTY(BlueprintReadWrite)
	UQPData* qp_helperData;
	
	/** 帮助id*/
	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//int32 qp_helperNum = 1;
	/** 提示id*/

	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//int32 qp_tipNum = 1;
	/** 段教程id*/

	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//int32 qp_courseNum = 1;

	/**保存设置的文件名字*/
	FString qp_SaveSlotName = TEXT("qp_helperSaveGame");
	/**保存设置的玩家id*/
	uint32 qp_UserIndex = 0;


	/** 设置新的帮助id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetHelperNum(int32 n);

	/** 设置新的提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetTipNum(int32 n);

	/** 设置新的短教程id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetCourseNum(int32 n);

	/** 设置新的帮助id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
		int32 QP_GetHelperNum();

	/** 设置新的提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
		int32 QP_GetTipNum();

	/** 设置新的短教程id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
		int32 QP_GetCourseNum();

	void QP_SaveHelperData();
	void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void QP_LoadHelperData();

	void QP_BindHelperData(const UQPData* data);


};
