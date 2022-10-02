// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QPWM_Object.generated.h"

/**
 * 
 */

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPWM_Object : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UQPWM_Object* QP_UQPWM_Object;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	TMap<FString,TArray<UObject*>> qp_objData;

	/**把用不到的对象放到这个里面*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Object")
	void QP_CollectObject(FString key, UObject* obj);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Object")
	UObject* QP_GetObject(FString key);


	/**异步加载*/
	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass,FString key, UQPData* data);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass, FSoftObjectPath& keys, UQPData* data);


	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftObjectPath> keys, UQPData* data);

	void QP_RequestAsyncLoadDeferred();*/
};
