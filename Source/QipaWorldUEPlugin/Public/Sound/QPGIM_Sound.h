// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Sound.generated.h"


class UQPData;
/**
 * 音频管理类 单纯的用于存储玩家数据
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Sound : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	/**数据管理器里的数据名字*/
	FString qp_soundDataName = "qp_soundDataName";
public:
	static UQPGIM_Sound* QP_UQPGIM_Sound;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/**声音数据*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPSound")
	UQPData* qp_soundData;
	
	//UPROPERTY()
	//UAudioComponent* qp_bgSound = nullptr;
	//UPROPERTY()
	//UAudioComponent* qp_UISound = nullptr;

	/*float qp_musicVolume = 1.0f;
	float qp_soundVolume = 1.0f;*/
	/**保存声音设置的文件名字*/
	FString qp_SaveSlotName = TEXT("qp_soundSaveGame");
	/**保存声音设置的玩家id*/
	uint32 qp_UserIndex = 0;

	
	/** Subsystem 没有BeginPlay，这个必须beginplay里调用,所以在initScene的蓝图里调用了，因为没有world，不能播放声音*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	void QP_BeginPlayInit();

	
	/** 用路径设置背景音乐*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_SetBgMusicByPath(const FString soundPath);

	/** 用sound设置背景音乐*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_SetBgMusicBySound(USoundBase* sound);

	/** 用路径播放背景音乐*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayBgMusicByPath(const FString soundPath);

	/** 用sound播放背景音乐*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayBgMusicBySound(USoundBase* sound);

	/** 播放背景音乐*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayBgMusic();


	/** 用路径设置点击ui的音效*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_SetClickUISoundByPath(const FString soundPath);

	/** 用sound设置点击ui的音效*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_SetClickUISoundBySound(USoundBase* sound);

	/** 用路径播放点击ui的音效*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayClickUISoundByPath(const FString soundPath);

	/** 用sound播放点击ui的音效*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayClickUISoundBySound(USoundBase* sound);

	/** 播放点击ui的音效*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//void QP_PlayClickUISound();

	/** 用路径播放一次性音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	void QP_Play2DSoundByPath(const FString soundPath);

	/** 用sound播放一次性音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	void QP_Play2DSoundBySound(USoundBase* sound);

	/** 设置音效大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	void QP_SetAllVolume(float v);

	/** 获得音效大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	float QP_GetAllVolume();

	/** 设置音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		void QP_SetMusicVolume(float v);

	/** 获得音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		float QP_GetMusicVolume();

	/** 设置音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		void QP_SetEffectVolume(float v);

	/** 获得音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		float QP_GetEffectVolume();
	/** 设置音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		void QP_SetUIVolume(float v);

	/** 获得音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		float QP_GetUIVolume();
	/** 设置音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		void QP_SetEnvironmentVolume(float v);

	/** 获得音乐大小*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
		float QP_GetEnvironmentVolume();
	//void QP_CreateAudioComponent(UAudioComponent*& audio,float volume, USoundBase* sound);
	/**音量变化的时候设置背景音乐和音效的音量*/
	void QP_SoundDataChange(const UQPData* data);
	/**退出游戏的时候保存*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	void QP_SaveSoundData();
	void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void QP_LoadSoundData();
	USoundBase* QP_CreateSoundBase(FString path);

};
