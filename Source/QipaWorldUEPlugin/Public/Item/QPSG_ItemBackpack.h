// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/QPSaveGame.h"
#include "QPSG_ItemBackpack.generated.h"

struct FQPItem;
/**
 * 帮助数据保存基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSG_ItemBackpack : public UQPSaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPHelper")
	TArray<FQPItem> qp_itemFoods;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPHelper")
	TArray<FQPItem> qp_itemTransforms;
};
