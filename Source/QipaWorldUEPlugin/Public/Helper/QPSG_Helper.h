// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPSG_Helper.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSG_Helper : public USaveGame
{
	GENERATED_BODY()
public:
	
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	int32 qp_helperNum = 1;

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	int32 qp_tipNum = 1;

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|Helper")
	int32 qp_courseNum = 1;
};
