// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Data.generated.h"

class UQPData;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Data : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

	UQPData* qp_baseData;

	TArray<UQPData*> qp_broadcastArray;
	TArray<UQPData*> qp_tempBroadcastArray;
public:
	static UQPGIM_Data* QP_UQPGIM_Data;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	virtual void Tick(float DeltaTime)override;

	virtual bool IsTickable()const override;

	virtual TStatId GetStatId() const override;

	/**这个千万不要轻易调用，
	*你直接get，没有会自动帮你创建，
	*你要是用这个，如果之前这个key下如果有个data，会直接被替换！！！*/
	UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	UQPData* QP_AddQPData(FString key,UQPData* data = nullptr);
	
	UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	UQPData* QP_GetQPData(FString key);

	UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_RemoveQPData(FString key);
	
	void QP_AddBroadcastUQPData(UQPData* data);
	void QP_RemoveBroadcastUQPData(UQPData* data);
};
