// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPSG_Sound.generated.h"

/**
 * 保存音乐设置数据的类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSG_Sound : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
    float qp_soundVolume = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
    float qp_musicVolume = 1.0f;

};
