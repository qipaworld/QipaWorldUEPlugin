// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/QPGIM_Sound.h"

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/QPDS_Default.h"
#include "Components/AudioComponent.h"
#include "Sound/QPSG_Sound.h"
#include "MetasoundSource.h"
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

	qp_soundData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData("UQPGIM_Sound");
	
	QP_LoadSoundData();
	
	//qp_loadMapName = UQPDS_Default::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Sound::Deinitialize()
{
	//if (qp_bgSound != nullptr) {
		//qp_bgSound->Stop();
	//}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
//	QP_SaveSoundData();
	Super::Deinitialize();
}

void UQPGIM_Sound::QP_BeginPlayInit()
{
	
	//FString soundPath = UQPDS_Default::QP_GET()->QP_DefaultBackgroundAudioPath;
	//bool autoPlay = UQPDS_Default::QP_GET()->QP_BackgroundAudioAutoPlay;
	
	//if (autoPlay) {
		//QP_PlayDisposablesSoundByPath(soundPath);
	///}//else if (soundPath != "None") {
		//QP_CreateAudioComponent(qp_bgSound, QP_GetMusicVolume(), QP_CreateSoundBase(soundPath));
	//}

	/*FString UISoundPath = UQPDS_Default::QP_GET()->QP_DefaultUIClickAudioPath;

	if (UISoundPath != "None") {
		QP_CreateAudioComponent(qp_UISound, QP_GetSoundVolume(), QP_CreateSoundBase(UISoundPath));
	}*/
}
//
//void UQPGIM_Sound::QP_SetBgMusicByPath(const FString soundPath)
//{
//	QP_SetBgMusicBySound(QP_CreateSoundBase(soundPath));
//}
//
//void UQPGIM_Sound::QP_SetBgMusicBySound(USoundBase* sound)
//{
//	QP_PlayDisposablesUISoundBySound(sound);
//	/*if (qp_bgSound != nullptr) {
//		qp_bgSound->SetSound(sound);
//	}
//	else {
//		QP_CreateAudioComponent(qp_bgSound, QP_GetMusicVolume(), sound);
//	}*/
//}
//
//void UQPGIM_Sound::QP_PlayBgMusicByPath(const FString soundPath)
//{
//	QP_SetBgMusicByPath(soundPath);
//	QP_PlayBgMusic();
//}
//
//void UQPGIM_Sound::QP_PlayBgMusicBySound(USoundBase* sound)
//{
//	QP_SetBgMusicBySound(sound);
//	QP_PlayBgMusic();
//}

//void UQPGIM_Sound::QP_PlayBgMusic()
//{
//	/*if (qp_bgSound != nullptr) {
//		qp_bgSound->Play();
//	}*/
//}

//
//void UQPGIM_Sound::QP_SetClickUISoundByPath(const FString soundPath)
//{
//	QP_SetClickUISoundBySound(QP_CreateSoundBase(soundPath));
//}

//void UQPGIM_Sound::QP_SetClickUISoundBySound(USoundBase* sound)
//{
//	if (qp_UISound != nullptr) {
//		qp_UISound->SetSound(sound);
//	}
//	else {
//		QP_CreateAudioComponent(qp_UISound, QP_GetSoundVolume(), sound);
//	}
//}

//void UQPGIM_Sound::QP_PlayClickUISoundByPath(const FString soundPath)
//{
//	QP_SetClickUISoundByPath(soundPath);
//	QP_PlayClickUISound();
//}

//void UQPGIM_Sound::QP_PlayClickUISoundBySound(USoundBase* sound)
//{
//	QP_SetClickUISoundBySound(sound);
//	QP_PlayClickUISound();
//}

//void UQPGIM_Sound::QP_PlayClickUISound()
//{
//	if (qp_UISound != nullptr) {
//		qp_UISound->Play();
//	}
//}

void UQPGIM_Sound::QP_Play2DSoundByPath(const FString soundPath)
{
	QP_Play2DSoundBySound(QP_CreateSoundBase(soundPath));
}

void UQPGIM_Sound::QP_Play2DSoundBySound(USoundBase* sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), sound);
}

void UQPGIM_Sound::QP_SetAllVolume(float v)
{
	qp_soundData->QP_Addfloat("allVolume",v);
}

float UQPGIM_Sound::QP_GetAllVolume()
{
	return qp_soundData->QP_Getfloat("allVolume");
}

void UQPGIM_Sound::QP_SetMusicVolume(float v)
{
	qp_soundData->QP_Addfloat("musicVolume", v);
}

float UQPGIM_Sound::QP_GetMusicVolume()
{
	return qp_soundData->QP_Getfloat("musicVolume");
}


void UQPGIM_Sound::QP_SetEffectVolume(float v)
{
	qp_soundData->QP_Addfloat("effectVolume", v);
}

float UQPGIM_Sound::QP_GetEffectVolume()
{
	return qp_soundData->QP_Getfloat("effectVolume");
}


void UQPGIM_Sound::QP_SetUIVolume(float v)
{
	qp_soundData->QP_Addfloat("UIVolume", v);
}

float UQPGIM_Sound::QP_GetUIVolume()
{
	return qp_soundData->QP_Getfloat("UIVolume");
}


void UQPGIM_Sound::QP_SetEnvironmentVolume(float v)
{
	qp_soundData->QP_Addfloat("environmentVolume", v);
}

float UQPGIM_Sound::QP_GetEnvironmentVolume()
{
	return qp_soundData->QP_Getfloat("environmentVolume");
}
//void UQPGIM_Sound::QP_CreateAudioComponent(UAudioComponent*& audio,float volume,USoundBase* sound) {
	//audio = UGameplayStatics::CreateSound2D(GetWorld(), sound, volume, 1.0f, 0.0f, nullptr, true);
	//audio->AddToRoot();
//}

void UQPGIM_Sound::QP_SoundDataChange(UQPData* data)
{
	//qp_musicVolume = qp_soundData->QP_Getfloat("musicVolume");
	//qp_soundVolume = qp_soundData->QP_Getfloat("soundVolume");
	//if (qp_bgSound != nullptr) {
	//	//qp_bgSound->SetPitchMultiplier(qp_pitch);
	//	qp_bgSound->SetVolumeMultiplier(QP_GetMusicVolume());
	//}
	//if (qp_UISound != nullptr) {
	//	//qp_UISound->SetPitchMultiplier(qp_pitch);
	//	qp_UISound->SetVolumeMultiplier(QP_GetSoundVolume());
	//}
}

void UQPGIM_Sound::QP_SaveSoundData()
{

	UQPSG_Sound* qp_soundSaveGame = Cast<UQPSG_Sound>(UGameplayStatics::CreateSaveGameObject(UQPSG_Sound::StaticClass()));
	if (qp_soundSaveGame)
	{

		// 设置（可选）委托。
		//FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		//qp_SavedDelegate.BindUObject(this, &UQPGIM_Sound::QP_SavedDelegate);
		
		qp_soundSaveGame->qp_musicVolume = QP_GetMusicVolume();
		qp_soundSaveGame->qp_allVolume = QP_GetAllVolume();
		qp_soundSaveGame->qp_UIVolume = QP_GetUIVolume();
		qp_soundSaveGame->qp_effectVolume = QP_GetEffectVolume();
		qp_soundSaveGame->qp_environmentVolume = QP_GetEnvironmentVolume();

		UGameplayStatics::SaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName, qp_UserIndex);
		// 启动异步保存进程。
		//UGameplayStatics::AsyncSaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName,qp_UserIndex, qp_SavedDelegate);
	}
}

void UQPGIM_Sound::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}

void UQPGIM_Sound::QP_LoadSoundData()
{
	UQPSG_Sound* qp_LoadSoundData = Cast<UQPSG_Sound>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (qp_LoadSoundData)
	{
		
		QP_SetMusicVolume(qp_LoadSoundData->qp_musicVolume);
		QP_SetAllVolume(qp_LoadSoundData->qp_allVolume);
		QP_SetEffectVolume(qp_LoadSoundData->qp_effectVolume);
		QP_SetUIVolume(qp_LoadSoundData->qp_UIVolume);
		QP_SetEnvironmentVolume(qp_LoadSoundData->qp_environmentVolume) ;
	}
	else 
	{
		QP_SetMusicVolume(1);
		QP_SetAllVolume(1);
		QP_SetEffectVolume(1);
		QP_SetUIVolume(1);
		QP_SetEnvironmentVolume(1);
	}
	
	//qp_handle = qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGIM_Sound::QP_BindSoundData);
	qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGIM_Sound::QP_SoundDataChange);

}

USoundBase* UQPGIM_Sound::QP_CreateSoundBase(FString path)
{
	return LoadObject<UMetaSoundSource>(nullptr,*path);
}
