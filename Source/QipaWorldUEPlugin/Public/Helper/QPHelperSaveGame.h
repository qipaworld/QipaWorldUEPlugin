// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPHelperSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPHelperSaveGame : public USaveGame
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
