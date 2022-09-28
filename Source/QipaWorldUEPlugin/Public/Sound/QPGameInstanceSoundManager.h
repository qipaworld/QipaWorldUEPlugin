// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGameInstanceSoundManager.generated.h"

class UQPData;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGameInstanceSoundManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/** 用了解除数据绑定用的 */
	//FDelegateHandle qp_handle;
public:
	static UQPGameInstanceSoundManager* QP_UQPGameInstanceSoundManager;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/***/
	UQPData* qp_soundData;
	
	UAudioComponent* qp_bgSound = nullptr;
	UAudioComponent* qp_UISound = nullptr;

	float qp_pitch = 1.0f;
	float qp_volume = 1.0f;
	/**保存游戏用的key和玩家id*/
	FString qp_SaveSlotName = TEXT("qp_soundSaveGame");;
	uint32 qp_UserIndex = 0;

	/** 独立加入的子关卡是否加载完成*/
	//UPROPERTY(BlueprintReadWrite)
	//	bool qp_isLoadMap = false;

	///** 独立加入的子关卡是否加载完成*/
	//UPROPERTY(BlueprintReadWrite)
	//	bool qp_isLoadSubMap = false;

	/////** 即将加载或者当前level的名字。*/

	////UPROPERTY(BlueprintReadWrite)
	////FString qp_loadMapName;

	/**加载成功后的回调*/
	//FLatentActionInfo qp_actionInfo;
	/** Subsystem 里没有beginplay，只能蓝图里调用*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_BeginPlayInit();

	
	/** 用资源路径设置背景音乐*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetBgMusicByPath(const FString soundPath);

	/** 用SoundBase设置背景音乐*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetBgMusicBySound(USoundBase* sound);

	/** 用资源路径播放背景音乐*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusicByPath(const FString soundPath);

	/** 用SoundBase播放背景音乐*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusicBySound(USoundBase* sound);

	/** 播放背景音乐*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusic();


	/** 用资源路径设置UI点击音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetClickUISoundByPath(const FString soundPath);

	/** 用SoundBase设置UI点击音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetClickUISoundBySound(USoundBase* sound);

	/** 用资源路径播放UI点击音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISoundByPath(const FString soundPath);

	/** 用SoundBase播放UI点击音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISoundBySound(USoundBase* sound);

	/** 播放UI点击音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISound();

	/** 用路径播放UI一次性的音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayDisposablesUISoundByPath(const FString soundPath);

	/** 用Sound播放UI一次性的音效*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayDisposablesUISoundBySound(USoundBase* sound);

	void QP_CreateAudioComponent(UAudioComponent*& audio, USoundBase* sound);

	void QP_BindSoundData(const UQPData* data);

	void QP_SaveSoundData();
	void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void QP_LoadSoundData();
	USoundBase* QP_CreateSoundBase(FString path);

};
