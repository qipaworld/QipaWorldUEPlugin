// QIPAWORLD


#include "Steam/QPGI_Steam.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "QPUtil.h"
#include "OnlineError.h"
#include "Interfaces/OnlineIdentityInterface.h"
UQPGI_Steam* UQPGI_Steam::qp_staticObject = nullptr;
bool UQPGI_Steam::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGI_Steam::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());

	qp_staticObject = this; 

	qp_steamData = UQPGIM_BaseData::qp_staticObject->QP_GetSteamData();
	qp_steamData->QP_LoadData("UQPGI_Steam");
	qp_steamData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_GetUQPData("_");
	qp_steamData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_SetIsSave(EQPDataKeyType::FNAME, EQPDataValueType::UQPDATA,false);
	//qp_soundData->QP_LoadData("UQPGI_Steam");
	//qp_soundVolumeData = qp_soundData->QP_GetUQPData("qp_soundVolumeData");
	//QP_LoadSoundData();

	//qp_loadMapName = UQPDS_Default::QP_GET()->QP_DefaultStartMap;
}

void UQPGI_Steam::Deinitialize()
{
	//if (qp_bgSound != nullptr) {
		//qp_bgSound->Stop();
	//}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();
	
	Super::Deinitialize();

	qp_staticObject = nullptr;
}
void UQPGI_Steam::QP_AddAchievement(FName qp_AchievementId, int32 qp_playerId, float num) {

	if (qp_AchievementId.IsNone()) {
		return;
	}
	if (qp_steamData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_GetboolExI(qp_playerId)) {

		return;
	}
	UQPData* d = qp_steamData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_GetUQPData(qp_AchievementId);
	if (d->QP_GetboolExI(qp_playerId)) {
		return;
	}
	d->QP_AddboolExI(qp_playerId, true);
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (Subsystem)
	{

		IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
		IOnlineAchievementsPtr Achievements = Subsystem->GetAchievementsInterface();


		if (Identity.IsValid() && Achievements.IsValid())
		{

			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(qp_playerId);
			if (UserId.IsValid())
			{

				Achievements->QueryAchievements(*UserId, FOnQueryAchievementsCompleteDelegate::CreateLambda(
					[this,Achievements, UserId, qp_AchievementId, num, qp_playerId,d](const FUniqueNetId& QueriedId, const bool bSuccess)
					{

						if (bSuccess)
						{
							FOnlineAchievementsWritePtr WriteObject = MakeShareable(new FOnlineAchievementsWrite());
							WriteObject->SetFloatStat(qp_AchievementId, num);  

							FOnlineAchievementsWriteRef WriteRef = WriteObject.ToSharedRef();
							Achievements->WriteAchievements(*UserId, WriteRef,
								FOnAchievementsWrittenDelegate::CreateLambda([this,qp_AchievementId, num, qp_playerId,d](const FUniqueNetId& PlayerId, bool bWriteSuccess)
									{

										if (num == 100&& bWriteSuccess) {

											qp_steamData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_AddboolExI(qp_playerId, true);
											qp_steamData->QP_SaveData("UQPGI_Steam");
										}
										else {
											d->QP_AddboolExI(qp_playerId, false);
										}
									}));
						}
						else
						{
							d->QP_AddboolExI(qp_playerId, false);
						}
					}));
			}
			else {
				d->QP_AddboolExI(qp_playerId, false);
			}
		}
		else {
			d->QP_AddboolExI(qp_playerId, false);
		}
	}
	else {
		d->QP_AddboolExI(qp_playerId, false);

	}


	
}
