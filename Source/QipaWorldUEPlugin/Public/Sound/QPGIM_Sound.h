// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Sound.generated.h"


class UQPData;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Sound : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/** ÓÃÁË½â³ýÊý¾Ý°ó¶¨ÓÃµÄ */
	//FDelegateHandle qp_handle;
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
	/**´æ·ÅÁËÒôÀÖµÄÊý¾Ý*/
	UPROPERTY(BlueprintReadWrite)
	UQPData* qp_soundData;
	
	UAudioComponent* qp_bgSound = nullptr;
	UAudioComponent* qp_UISound = nullptr;

	float qp_musicVolume = 1.0f;
	float qp_soundVolume = 1.0f;
	/**±£´æÓÎÏ·ÓÃµÄkeyºÍÍæ¼Òid*/
	FString qp_SaveSlotName = TEXT("qp_soundSaveGame");;
	uint32 qp_UserIndex = 0;

	/** ¶ÀÁ¢¼ÓÈëµÄ×Ó¹Ø¿¨ÊÇ·ñ¼ÓÔØÍê³É*/
	//UPROPERTY(BlueprintReadWrite)
	//	bool qp_isLoadMap = false;

	///** ¶ÀÁ¢¼ÓÈëµÄ×Ó¹Ø¿¨ÊÇ·ñ¼ÓÔØÍê³É*/
	//UPROPERTY(BlueprintReadWrite)
	//	bool qp_isLoadSubMap = false;

	/////** ¼´½«¼ÓÔØ»òÕßµ±Ç°levelµÄÃû×Ö¡£*/

	////UPROPERTY(BlueprintReadWrite)
	////FString qp_loadMapName;

	/**¼ÓÔØ³É¹¦ºóµÄ»Øµ÷*/
	//FLatentActionInfo qp_actionInfo;
	/** Subsystem ÀïÃ»ÓÐbeginplay£¬Ö»ÄÜÀ¶Í¼Àïµ÷ÓÃ*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_BeginPlayInit();

	
	/** ÓÃ×ÊÔ´Â·¾¶ÉèÖÃ±³¾°ÒôÀÖ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetBgMusicByPath(const FString soundPath);

	/** ÓÃSoundBaseÉèÖÃ±³¾°ÒôÀÖ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetBgMusicBySound(USoundBase* sound);

	/** ÓÃ×ÊÔ´Â·¾¶²¥·Å±³¾°ÒôÀÖ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusicByPath(const FString soundPath);

	/** ÓÃSoundBase²¥·Å±³¾°ÒôÀÖ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusicBySound(USoundBase* sound);

	/** ²¥·Å±³¾°ÒôÀÖ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayBgMusic();


	/** ÓÃ×ÊÔ´Â·¾¶ÉèÖÃUIµã»÷ÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetClickUISoundByPath(const FString soundPath);

	/** ÓÃSoundBaseÉèÖÃUIµã»÷ÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_SetClickUISoundBySound(USoundBase* sound);

	/** ÓÃ×ÊÔ´Â·¾¶²¥·ÅUIµã»÷ÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISoundByPath(const FString soundPath);

	/** ÓÃSoundBase²¥·ÅUIµã»÷ÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISoundBySound(USoundBase* sound);

	/** ²¥·ÅUIµã»÷ÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayClickUISound();

	/** ÓÃÂ·¾¶²¥·ÅUIÒ»´ÎÐÔµÄÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayDisposablesUISoundByPath(const FString soundPath);

	/** ÓÃSound²¥·ÅUIÒ»´ÎÐÔµÄÒôÐ§*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	void QP_PlayDisposablesUISoundBySound(USoundBase* sound);

	void QP_CreateAudioComponent(UAudioComponent*& audio,float volume, USoundBase* sound);

	void QP_BindSoundData(const UQPData* data);

	void QP_SaveSoundData();
	void QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void QP_LoadSoundData();
	USoundBase* QP_CreateSoundBase(FString path);

};
