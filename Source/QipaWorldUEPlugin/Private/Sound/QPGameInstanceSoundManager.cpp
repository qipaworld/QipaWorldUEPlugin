// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/QPGameInstanceSoundManager.h"
#include "Data/QPGameInstanceDataManager.h"
#include "Data/QPData.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/QPDeveloperSettings.h"
#include "Components/AudioComponent.h"
#include "Sound/QPSoundSaveGame.h"


UQPGameInstanceSoundManager* UQPGameInstanceSoundManager::QP_UQPGameInstanceSoundManager = nullptr;


bool UQPGameInstanceSoundManager::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGameInstanceSoundManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGameInstanceSoundManager = this;

	qp_soundData = UQPGameInstanceDataManager::QP_UQPGameInstanceDataManager->QP_GetQPData("soundData");
	
	QP_LoadSoundData();
	
	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGameInstanceSoundManager::Deinitialize()
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->Stop();
	}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	Super::Deinitialize();
}

void UQPGameInstanceSoundManager::QP_BeginPlayInit()
{
	
	FString soundPath = UQPDeveloperSettings::QP_GET()->QP_DefaultBackgroundAudioPath;
	bool autoPlay = UQPDeveloperSettings::QP_GET()->QP_BackgroundAudioAutoPlay;
	
	if (autoPlay) {
		QP_PlayBgMusicByPath(soundPath);
	}else if (soundPath != "None") {
		QP_CreateAudioComponent(qp_UISound, QP_CreateSoundBase(soundPath));
	}

	FString UISoundPath = UQPDeveloperSettings::QP_GET()->QP_DefaultUIClickAudioPath;

	if (UISoundPath != "None") {
		QP_CreateAudioComponent(qp_UISound, QP_CreateSoundBase(UISoundPath));
	}
}

void UQPGameInstanceSoundManager::QP_SetBgMusicByPath(const FString soundPath)
{
	QP_SetBgMusicBySound(QP_CreateSoundBase(soundPath));
}

void UQPGameInstanceSoundManager::QP_SetBgMusicBySound(USoundBase* sound)
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->SetSound(sound);
	}
	else {
		QP_CreateAudioComponent(qp_bgSound, sound);
	}
}

void UQPGameInstanceSoundManager::QP_PlayBgMusicByPath(const FString soundPath)
{
	QP_SetBgMusicByPath(soundPath);
	QP_PlayBgMusic();
}

void UQPGameInstanceSoundManager::QP_PlayBgMusicBySound(USoundBase* sound)
{
	QP_SetBgMusicBySound(sound);
	QP_PlayBgMusic();
}

void UQPGameInstanceSoundManager::QP_PlayBgMusic()
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->Play();
	}
}


void UQPGameInstanceSoundManager::QP_SetClickUISoundByPath(const FString soundPath)
{
	QP_SetClickUISoundBySound(QP_CreateSoundBase(soundPath));
}

void UQPGameInstanceSoundManager::QP_SetClickUISoundBySound(USoundBase* sound)
{
	if (qp_UISound != nullptr) {
		qp_UISound->SetSound(sound);
	}
	else {
		QP_CreateAudioComponent(qp_UISound, sound);
	}
}

void UQPGameInstanceSoundManager::QP_PlayClickUISoundByPath(const FString soundPath)
{
	QP_SetClickUISoundByPath(soundPath);
	QP_PlayClickUISound();
}

void UQPGameInstanceSoundManager::QP_PlayClickUISoundBySound(USoundBase* sound)
{
	QP_SetClickUISoundBySound(sound);
	QP_PlayClickUISound();
}

void UQPGameInstanceSoundManager::QP_PlayClickUISound()
{
	if (qp_UISound != nullptr) {
		qp_UISound->Play();
	}
}

void UQPGameInstanceSoundManager::QP_PlayDisposablesUISoundByPath(const FString soundPath)
{
	QP_PlayDisposablesUISoundBySound(QP_CreateSoundBase(soundPath));
}

void UQPGameInstanceSoundManager::QP_PlayDisposablesUISoundBySound(USoundBase* sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), sound, qp_volume, qp_pitch);
}

void UQPGameInstanceSoundManager::QP_CreateAudioComponent(UAudioComponent*& audio,USoundBase* sound) {
	audio = UGameplayStatics::CreateSound2D(GetWorld(), sound, qp_volume, qp_pitch, 0.0f, nullptr, true);
}

void UQPGameInstanceSoundManager::QP_BindSoundData(const UQPData* data)
{
	qp_pitch = qp_soundData->QP_Getfloat("pitch");
	qp_volume = qp_soundData->QP_Getfloat("volume");
	if (qp_bgSound != nullptr) {
		qp_bgSound->SetPitchMultiplier(qp_pitch);
		qp_bgSound->SetVolumeMultiplier(qp_volume);
	}
	if (qp_UISound != nullptr) {
		qp_UISound->SetPitchMultiplier(qp_pitch);
		qp_UISound->SetVolumeMultiplier(qp_volume);
	}
}

void UQPGameInstanceSoundManager::QP_SaveSoundData()
{
	UQPSoundSaveGame* qp_soundSaveGame = Cast<UQPSoundSaveGame>(UGameplayStatics::CreateSaveGameObject(UQPSoundSaveGame::StaticClass()));
	if (qp_soundSaveGame)
	{
		// 设置（可选）委托。
		FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		qp_SavedDelegate.BindUObject(this, &UQPGameInstanceSoundManager::QP_SavedDelegate);

		qp_soundSaveGame->qp_pitch = qp_pitch;
		qp_soundSaveGame->qp_volume = qp_volume;

		// 启动异步保存进程。
		UGameplayStatics::AsyncSaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName,qp_UserIndex, qp_SavedDelegate);
	}
}

void UQPGameInstanceSoundManager::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}

void UQPGameInstanceSoundManager::QP_LoadSoundData()
{
	UQPSoundSaveGame* qp_LoadSoundData = Cast<UQPSoundSaveGame>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (qp_LoadSoundData)
	{
		qp_pitch = qp_LoadSoundData->qp_pitch;
		qp_volume = qp_LoadSoundData->qp_volume;
	}
	else 
	{
		qp_pitch = 1.0f;
		qp_volume = 1.0f;
	}
	qp_soundData->QP_Addfloat("pitch", qp_pitch);
	qp_soundData->QP_Addfloat("volume", qp_volume);
	//qp_handle = qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGameInstanceSoundManager::QP_BindSoundData);
	qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGameInstanceSoundManager::QP_BindSoundData);

}

USoundBase* UQPGameInstanceSoundManager::QP_CreateSoundBase(FString path)
{
	return LoadObject<USoundWave>(nullptr, *path);
}
