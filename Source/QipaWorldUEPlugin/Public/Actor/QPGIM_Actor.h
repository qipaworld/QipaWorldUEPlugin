// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Actor.generated.h"

/**
 * 管理actor的类，还没写
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Actor : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UQPGIM_Actor* qp_staticObject;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	TMap<FName, TArray<AActor*>> qp_actorData;

	/**把用不到的对象放到这个里面，里面是个数组。
	* @param key - 对象类型。
	* @param actor - 对象。
	* @warning 每个类型可以存储多个对象。
	*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPActor")
	//void QP_CollectActor(FString key, AActor* actor);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPActor")
	void QP_AddActor(const FName& key, AActor* actor,bool ishid = false);
	//int32 qp_getNum = 0;
	/**通过类型在这里面取出对象
	* @param key - 对象类型。
	* @warning 每个类型可以取出多个对象。
	*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPActor")
	//AActor* QP_GetActor(FString key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPActor")
	AActor* QP_PopActor(const FName& key, bool isshow = false);

	void QP_BindMapData(class UQPData* data);

	/**异步加载*/
	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass,FString key, UQPData* data);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass, FSoftActorPath& keys, UQPData* data);


	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Assets")
	void QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftActorPath> keys, UQPData* data);

	void QP_RequestAsyncLoadDeferred();*/
};
