// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_LoadAssets.generated.h"


UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_LoadAssets : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static UQPGIM_LoadAssets* QP_UQPGIM_LoadAssets;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	//virtual void Tick(float DeltaTime)override;

	//virtual bool IsTickable()const override;

	//virtual TStatId GetStatId() const override;

	/**Òì²½¼ÓÔØ*/
	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	UQPData* QP_RequestAsyncLoad(FString key, UQPData* data);*/

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	//	UQPData* QP_GetQPData(FString key);

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	//	void QP_RemoveQPData(FString key);

	//void QP_AddBroadcastUQPData(UQPData* data);
	//void QP_RemoveBroadcastUQPData(UQPData* data);
};