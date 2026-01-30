// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataAsset/QPD_Items.h"
#include "Item/QPDA_Item.h"
#include "GameplayEffect.h"

#include "QPGIM_Item.generated.h"

class AQPMonster;
struct FQPItem;
class UQPData;
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Item : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UQPGIM_Item* qp_staticObject;
	virtual void QP_InitStaticObject();

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld")
	UQPData* qp_itemQPData;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPData")
	TObjectPtr< UQPD_Items> qp_defaultItemActors;

	
	//TObjectPtr< UQPD_Items> qp_defaultActors;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	AActor* QP_GetDefaultItemActor(FName n,FTransform T);
	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	void QP_AddItemActor(const FName& key, AActor* actor,bool ishid = false);
	
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	//AActor* QP_PopActor(const FName& key, bool isshow = false);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")

	AActor* QP_GetItemActor(const FName& n, FTransform t, bool isshow = false);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	UQPDA_Item* QP_GetItemData(const FName& n);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	FQPItem& QP_GetPlayerItem(int index);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	void QP_UsePlayerItem(int index);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	bool QP_AddPlayerItem(FQPItem& i);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	UQPData* QP_GetItemQPData();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	UTexture2D* QP_GetItemTexture2D(const FName& key);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	float QP_GetPlayerItemDataScale(int index);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	int QP_GetPlayerItemFreshType(int index);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	FName QP_GetPlayerItemName(int index);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	UTexture2D* QP_GetPlayerItemTexture2D(int index);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	bool QP_IsPlayerItem(int index);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	bool QP_CheckPlayerItemShelfLife(int index);

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	//const FQPItem& QP_GetPlayerItemDataEx(int index)
		//;
	UGameplayEffect* QP_GetItemGE(FQPItem& n);

	void QP_UseItem(FQPItem& t, AQPMonster*m);

	TMap<FName, UGameplayEffect*> qp_itemEffects;
	TMap<FName, UQPDA_Item*> qp_itemDatas;

	
};
