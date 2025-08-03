// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPGIM_BaseData.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "OnlineError.h"
#include "Interfaces/OnlineUserInterface.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "QPGI_Online.generated.h"

/**
 *
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGI_Online : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
public:
	static UQPGI_Online* qp_staticObject;
	virtual void QP_InitStaticObject();

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/
	UQPData* qp_onlineData;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();


	IOnlineUserPtr qp_userInterface = nullptr;
	IOnlineIdentityPtr qp_identityInterface = nullptr;
	FUniqueNetIdPtr qp_userId = nullptr;
	IOnlineAchievementsPtr qp_achievements = nullptr;
	IOnlineStatsPtr qp_statsInterface = nullptr;
	void QP_Init();
	
	void QP_QueryUserInfo(int32 LocalUserNum, bool bWasSuccessful, const TArray<TSharedRef<const FUniqueNetId>>& UserIds, const FString& ErrorStr);
	void QP_LogoutComplete(int32 UserNum, bool bWasSuccessful);
	void QP_LoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void QP_LogInUI();
	bool qp_isLongining = false;
	bool qp_isSwitching = false;
	bool qp_isInit = false;
	FString qp_loginType;

	UFUNCTION(BlueprintCallable)
	void QP_UploadStats(FName statsId,float num);

	UFUNCTION(BlueprintCallable)
	void QP_AddAchievement(FName qp_AchievementId,int32 qp_playerId = 0,float num = 100);

	UFUNCTION(BlueprintCallable)
	void QP_StartLogin(FString loginType = "persistentauth");

	UFUNCTION(BlueprintCallable)
	void QP_StartLogout();

	UFUNCTION(BlueprintCallable)
	void QP_StartSwitchAccounts();
	UFUNCTION(BlueprintCallable)
	FString QP_GetPlatform();

	UFUNCTION(BlueprintCallable)
	void QP_LoadUserData();

	UFUNCTION(BlueprintCallable)
	FString QP_GetPlatformOnline();

	void QP_QueryAchievements();
	void QP_QueryStats();
	void QP_QueryAllData();
};
