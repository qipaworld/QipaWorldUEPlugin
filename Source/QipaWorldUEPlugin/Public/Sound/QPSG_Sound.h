// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/QPSaveGame.h"
#include "QPSG_Sound.generated.h"

USTRUCT()
struct FQPSoundSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	float qp_value = 1;
};
/**
 * 保存音乐设置数据的类 废弃
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSG_Sound : public UQPSaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FQPSoundSaveData> qp_soundDatas;
	inline void QP_CheckValue(int32 i) {
		while (!qp_soundDatas.IsValidIndex(i))
		{
			qp_soundDatas.Emplace(FQPSoundSaveData());
		}
	}
	inline float QP_GetValue(int32 i) {
		QP_CheckValue(i);
		return qp_soundDatas[i].qp_value;
	}
	inline void QP_SetValue(int32 i,float v) {
		QP_CheckValue(i);
		qp_soundDatas[i].qp_value = v;
	}
   /* float qp_allVolume = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
    float qp_musicVolume = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
	float qp_effectVolume = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
	float qp_UIVolume = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSound")
	float qp_environmentVolume = 1.0f;*/

};
