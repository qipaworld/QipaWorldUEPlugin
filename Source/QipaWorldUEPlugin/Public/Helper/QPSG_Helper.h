// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPSG_Helper.generated.h"

/**
 * 帮助数据保存基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSG_Helper : public USaveGame
{
	GENERATED_BODY()
public:
	
	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//TMap<FString, FString> qp_helperData;
	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//TMap<FString, FString> qp_tipData;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPHelper")
	TMap<FString, FString> qp_helperData;

	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//FString qp_helperName;
	//UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	//FString qp_tipName;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPHelper")
	FString qp_helperName;
};
