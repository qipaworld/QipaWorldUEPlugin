// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/QPGIM_Sound.h"

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/QPDeveloperSettings.h"
#include "Components/AudioComponent.h"
#include "Sound/QPSoundSaveGame.h"
//#include "UObject/ConstructorHelpers.h"

UQPGIM_Sound* UQPGIM_Sound::QP_UQPGIM_Sound = nullptr;


bool UQPGIM_Sound::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Sound::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPGIM_Sound = this;

	qp_soundData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData("soundData");
	
	QP_LoadSoundData();
	
	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Sound::Deinitialize()
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->Stop();
	}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	Super::Deinitialize();
}

void UQPGIM_Sound::QP_BeginPlayInit()
{
	
	FString soundPath = UQPDeveloperSettings::QP_GET()->QP_DefaultBackgroundAudioPath;
	bool autoPlay = UQPDeveloperSettings::QP_GET()->QP_BackgroundAudioAutoPlay;
	
	if (autoPlay) {
		QP_PlayBgMusicByPath(soundPath);
	}else if (soundPath != "None") {
		QP_CreateAudioComponent(qp_UISound, qp_musicVolume, QP_CreateSoundBase(soundPath));
	}

	FString UISoundPath = UQPDeveloperSettings::QP_GET()->QP_DefaultUIClickAudioPath;

	if (UISoundPath != "None") {
		QP_CreateAudioComponent(qp_UISound, qp_soundVolume, QP_CreateSoundBase(UISoundPath));
	}
}

void UQPGIM_Sound::QP_SetBgMusicByPath(const FString soundPath)
{
	QP_SetBgMusicBySound(QP_CreateSoundBase(soundPath));
}

void UQPGIM_Sound::QP_SetBgMusicBySound(USoundBase* sound)
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->SetSound(sound);
	}
	else {
		QP_CreateAudioComponent(qp_bgSound, qp_musicVolume, sound);
	}
}

void UQPGIM_Sound::QP_PlayBgMusicByPath(const FString soundPath)
{
	QP_SetBgMusicByPath(soundPath);
	QP_PlayBgMusic();
}

void UQPGIM_Sound::QP_PlayBgMusicBySound(USoundBase* sound)
{
	QP_SetBgMusicBySound(sound);
	QP_PlayBgMusic();
}

void UQPGIM_Sound::QP_PlayBgMusic()
{
	if (qp_bgSound != nullptr) {
		qp_bgSound->Play();
	}
}


void UQPGIM_Sound::QP_SetClickUISoundByPath(const FString soundPath)
{
	QP_SetClickUISoundBySound(QP_CreateSoundBase(soundPath));
}

void UQPGIM_Sound::QP_SetClickUISoundBySound(USoundBase* sound)
{
	if (qp_UISound != nullptr) {
		qp_UISound->SetSound(sound);
	}
	else {
		QP_CreateAudioComponent(qp_UISound, qp_soundVolume, sound);
	}
}

void UQPGIM_Sound::QP_PlayClickUISoundByPath(const FString soundPath)
{
	QP_SetClickUISoundByPath(soundPath);
	QP_PlayClickUISound();
}

void UQPGIM_Sound::QP_PlayClickUISoundBySound(USoundBase* sound)
{
	QP_SetClickUISoundBySound(sound);
	QP_PlayClickUISound();
}

void UQPGIM_Sound::QP_PlayClickUISound()
{
	if (qp_UISound != nullptr) {
		qp_UISound->Play();
	}
}

void UQPGIM_Sound::QP_PlayDisposablesUISoundByPath(const FString soundPath)
{
	QP_PlayDisposablesUISoundBySound(QP_CreateSoundBase(soundPath));
}

void UQPGIM_Sound::QP_PlayDisposablesUISoundBySound(USoundBase* sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), sound, qp_soundVolume, 1.0f);
}

void UQPGIM_Sound::QP_CreateAudioComponent(UAudioComponent*& audio,float volume,USoundBase* sound) {
	audio = UGameplayStatics::CreateSound2D(GetWorld(), sound, volume, 1.0f, 0.0f, nullptr, true);
}

void UQPGIM_Sound::QP_BindSoundData(const UQPData* data)
{
	qp_musicVolume = qp_soundData->QP_Getfloat("musicVolume");
	qp_soundVolume = qp_soundData->QP_Getfloat("soundVolume");
	if (qp_bgSound != nullptr) {
		//qp_bgSound->SetPitchMultiplier(qp_pitch);
		qp_bgSound->SetVolumeMultiplier(qp_musicVolume);
	}
	if (qp_UISound != nullptr) {
		//qp_UISound->SetPitchMultiplier(qp_pitch);
		qp_UISound->SetVolumeMultiplier(qp_soundVolume);
	}
}

void UQPGIM_Sound::QP_SaveSoundData()
{
	UQPSoundSaveGame* qp_soundSaveGame = Cast<UQPSoundSaveGame>(UGameplayStatics::CreateSaveGameObject(UQPSoundSaveGame::StaticClass()));
	if (qp_soundSaveGame)
	{
		// 设置（可选）委托。
		FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		qp_SavedDelegate.BindUObject(this, &UQPGIM_Sound::QP_SavedDelegate);

		qp_soundSaveGame->qp_musicVolume = qp_musicVolume;
		qp_soundSaveGame->qp_soundVolume = qp_soundVolume;

		// 启动异步保存进程。
		UGameplayStatics::AsyncSaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName,qp_UserIndex, qp_SavedDelegate);
	}
}

void UQPGIM_Sound::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}

void UQPGIM_Sound::QP_LoadSoundData()
{
	UQPSoundSaveGame* qp_LoadSoundData = Cast<UQPSoundSaveGame>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (qp_LoadSoundData)
	{
		qp_musicVolume = qp_LoadSoundData->qp_musicVolume;
		qp_soundVolume = qp_LoadSoundData->qp_soundVolume;
	}
	else 
	{
		qp_musicVolume = 1.0f;
		qp_soundVolume = 1.0f;
	}
	qp_soundData->QP_Addfloat("musicVolume", qp_musicVolume);
	qp_soundData->QP_Addfloat("soundVolume", qp_soundVolume);
	//qp_handle = qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGIM_Sound::QP_BindSoundData);
	qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGIM_Sound::QP_BindSoundData);

}

USoundBase* UQPGIM_Sound::QP_CreateSoundBase(FString path)
{
	
	return LoadObject<USoundWave>(nullptr,*path);
}
