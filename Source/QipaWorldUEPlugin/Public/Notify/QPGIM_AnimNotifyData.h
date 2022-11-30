// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_AnimNotifyData.generated.h"


class UQPData;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_AnimNotifyData : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FString qp_animNotifyDataName = "qp_animNotifyDataName";
public:
	static UQPGIM_AnimNotifyData* QP_UQPGIM_AnimNotifyData;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/**声音数据*/
	UPROPERTY(BlueprintReadWrite)
	UQPData* qp_animNotifyData;
	
	
	/** 获得根数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|NotifyData")
	UQPData* QP_GetNotifyBaseData();

	/** 获得数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|NotifyData")
	UQPData* QP_GetNotifyData(FString name);

	/** 获得数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|NotifyData")
	UQPData* QP_AddNotifyData(FString name);

};
