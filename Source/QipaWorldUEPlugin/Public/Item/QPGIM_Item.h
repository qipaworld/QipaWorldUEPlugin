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
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Item : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UQPGIM_Item* qp_staticObject;
	virtual void QP_InitStaticObject();
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

	UGameplayEffect* QP_GetItemGE(FQPItem& n);

	void QP_UseItem(TArray<FQPItem>& t,int32 index, AQPMonster*m);

	TMap<FName, UGameplayEffect*> qp_itemEffects;
};
