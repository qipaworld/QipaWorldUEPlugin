// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QPSoundSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSoundSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    float qp_soundVolume = 1.0f;
    float qp_musicVolume = 1.0f;

};
