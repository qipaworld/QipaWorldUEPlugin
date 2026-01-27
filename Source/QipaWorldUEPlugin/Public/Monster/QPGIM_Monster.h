// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataAsset/QPD_Monsters.h"
//#include "Item/QPDA_Monster.h"
#include "QPGIM_Monster.generated.h"

/**
 * 管理actor的类，还没写
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Monster : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UQPGIM_Monster* qp_staticObject;
	virtual void QP_InitStaticObject();
	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPData")
	TObjectPtr< UQPD_Monsters> qp_defaultMonsters;

	
	//TObjectPtr< UQPD_Monsters> qp_defaultActors;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	AActor* QP_GetDefaultMonster(FName n,FTransform T);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	void QP_AddMonster(const FName& key, AActor* actor,bool ishid = false);
	
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	//AActor* QP_PopActor(const FName& key, bool isshow = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")

	AActor* QP_GetMonster(const FName& n, FTransform t, bool isshow = false);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	UQPDA_Character* QP_GetMonsterData(const FName& n);
};
