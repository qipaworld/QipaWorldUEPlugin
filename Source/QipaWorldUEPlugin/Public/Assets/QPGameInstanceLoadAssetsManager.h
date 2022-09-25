// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGameInstanceLoadAssetsManager.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGameInstanceLoadAssetsManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static UQPGameInstanceLoadAssetsManager* QP_UQPGameInstanceLoadAssetsManager;

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

	/**“Ï≤Ωº”‘ÿ*/
	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	UQPData* QP_RequestAsyncLoad(FString key, UQPData* data);*/

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	//	UQPData* QP_GetQPData(FString key);

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Data")
	//	void QP_RemoveQPData(FString key);

	//void QP_AddBroadcastUQPData(UQPData* data);
	//void QP_RemoveBroadcastUQPData(UQPData* data);
};
