// QIPAWORLD


#include "Online/QPGI_Online.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "QPUtil.h"
#include "OnlineError.h"
#include "Interfaces/OnlineUserInterface.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
UQPGI_Online* UQPGI_Online::qp_staticObject = nullptr;
bool UQPGI_Online::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGI_Online::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());

	QP_InitStaticObject();

	qp_onlineData = UQPGIM_BaseData::qp_staticObject->QP_GetOnlineData();
	qp_onlineData->QP_LoadData("UQPGI_Online");
	qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_GetUQPData("_");
	qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_SetIsSave(EQPDataKeyType::FNAME, EQPDataValueType::UQPDATA, false);
	//qp_soundData->QP_LoadData("UQPGI_Online");
	//qp_soundVolumeData = qp_soundData->QP_GetUQPData("qp_soundVolumeData");
	//QP_LoadSoundData();

	//qp_loadMapName = UQPDS_Default::QP_GET()->QP_DefaultStartMap;
}
void UQPGI_Online::QP_InitStaticObject() {
	UQPGI_Online::qp_staticObject = this;
}
void UQPGI_Online::Deinitialize()
{
	//if (qp_bgSound != nullptr) {
		//qp_bgSound->Stop();
	//}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();

	Super::Deinitialize();

	qp_staticObject = nullptr;
}
void UQPGI_Online::QP_StartLogout() {
	/*IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineIdentityPtr IdentityInterface = Subsystem->GetIdentityInterface();
		if (IdentityInterface.IsValid())
		{
			IdentityInterface->Logout(0);
		}
	}*/
}
void UQPGI_Online::QP_LoadUserData() 
{

	IOnlineUserPtr UserInterface = Online::GetUserInterface(GetWorld());
	if (UserInterface.IsValid())
	{
		
		IOnlineIdentityPtr IdentityInterface = IOnlineSubsystem::Get()->GetIdentityInterface();
		
		if (IdentityInterface.IsValid())
		{
			FUniqueNetIdPtr UserId = IdentityInterface->GetUniquePlayerId(0);
			//TArray<TSharedRef<const FUniqueNetId>> Users;

			if (UserId.IsValid())
			{
				UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin",true);

				FDelegateHandle Handle = UserInterface->AddOnQueryUserInfoCompleteDelegate_Handle(
					0,
					FOnQueryUserInfoCompleteDelegate::CreateLambda(
						[UserInterface, UserId](int32 LocalUserNum, bool bWasSuccessful, const TArray<TSharedRef<const FUniqueNetId>>& UserIds, const FString& ErrorStr)
						{
							if (bWasSuccessful)
							{
								TSharedPtr<const FOnlineUser> UserInfo = UserInterface->GetUserInfo(LocalUserNum, *UserId);
								if (UserInfo)
								{

									UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_AddFString("userName", UserInfo->GetDisplayName());
								}
							}
							else
							{

							}
						})
				);
				TArray<TSharedRef<const FUniqueNetId>> Users;
				Users.Add(UserId.ToSharedRef());

				UserInterface->QueryUserInfo(0, Users);

			}
			else {
				UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", false);
			}

		}
		// 异步请求用户信息（包括 DisplayName）
		
	}

	
	
}
void UQPGI_Online::QP_StartSwitchAccounts() {
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineIdentityPtr IdentityInterface = Subsystem->GetIdentityInterface();
		if (IdentityInterface.IsValid())
		{

			IdentityInterface->AddOnLogoutCompleteDelegate_Handle(0,
				FOnLogoutCompleteDelegate::CreateLambda([this](int32 UserNum, bool bWasSuccessful)
					{
						if (bWasSuccessful)
						{
							UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", false);

							QP_StartLogin();
						}
						
					}));
			//int32 LocalUserNum = 0; // 通常为 0，表示本地第一个用户

			IdentityInterface->Logout(0);
		}
	}
}



void UQPGI_Online::QP_StartLogin() {
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineIdentityPtr IdentityInterface = OnlineSub->GetIdentityInterface();

		if (IdentityInterface.IsValid())
		{
			IdentityInterface->OnLoginCompleteDelegates->AddLambda(
				[this](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
				{

					if (!bWasSuccessful) {
						Online::GetExternalUIInterface(GetWorld())->ShowLoginUI(0, true, true, FOnLoginUIClosedDelegate::CreateLambda(
							[this](TSharedPtr<const FUniqueNetId> UniqueId, const int ControllerIndex, const FOnlineError& Result) {
								if (Result.WasSuccessful())
								{
									UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", true);

									QP_LoadUserData();
									//UE_LOG(LogTemp, Log, TEXT("Login Success"));
								}
								else
								{
									UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", false);

									//UE_LOG(LogTemp, Warning, TEXT("Login Failed: %s"), *Result.ErrorMessage.ToString());
								}
							}));
					}
					else {
						UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", true);

						QP_LoadUserData();
					}
					
				});
			// 使用 IdentityInterface，比如调用 Login
			FOnlineAccountCredentials Credentials(TEXT("accountportal"), TEXT(""), TEXT(""));
			IdentityInterface->Login(0, Credentials);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("IdentityInterface error！"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("not  OnlineSubsystem！"));
	}
}
void UQPGI_Online::QP_AddAchievement(FName qp_AchievementId, int32 qp_playerId, float num) {

	if (qp_AchievementId.IsNone()) {
		return;
	}
	if (qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_GetboolExI(qp_playerId)) {

		return;
	}
	UQPData* d = qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_GetUQPData(qp_AchievementId);
	if (d->QP_GetboolExI(qp_playerId)) {
		return;
	}
	d->QP_AddboolExI(qp_playerId, true);
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
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
					[this, Achievements, UserId, qp_AchievementId, num, qp_playerId, d](const FUniqueNetId& QueriedId, const bool bSuccess)
					{

						if (bSuccess)
						{
							FOnlineAchievementsWritePtr WriteObject = MakeShareable(new FOnlineAchievementsWrite());
							WriteObject->SetFloatStat(qp_AchievementId, num);

							FOnlineAchievementsWriteRef WriteRef = WriteObject.ToSharedRef();
							Achievements->WriteAchievements(*UserId, WriteRef,
								FOnAchievementsWrittenDelegate::CreateLambda([this, qp_AchievementId, num, qp_playerId, d](const FUniqueNetId& PlayerId, bool bWriteSuccess)
									{
										
										if (num == 100 && bWriteSuccess) {

											qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_AddboolExI(qp_playerId, true);
											qp_onlineData->QP_SaveData("UQPGI_Online");
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

FString UQPGI_Online::QP_GetPlatform() {

	FString PlatformService;
	/*if (GConfig->GetString(
		TEXT("/Script/OnlineSubsystemUtils.OnlineEngineInterfaceImpl"),
		TEXT("DefaultPlatformService"),
		PlatformService,
		GEngineIni))
	{
		UQPUtil::QP_LOG(PlatformService + "___________________________________");
		return PlatformService;
	}*/

	/*if (!)
	{
		GConfig->GetString(TEXT("/Script/OnlineSubsystemUtils.OnlineEngineInterfaceImpl"), TEXT("DefaultPlatformService"), PlatformService, GEngineIni);

	}*/
	GConfig->GetString(TEXT("OnlineSubsystem"), TEXT("DefaultPlatformService"), PlatformService, GEngineIni);
	return PlatformService;

	
}

FString UQPGI_Online::QP_GetPlatformOnline() {


	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		return OnlineSub->GetSubsystemName().ToString();
	}

	return "NULL";
}


