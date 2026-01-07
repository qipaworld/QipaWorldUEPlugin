// QIPAWORLD


#include "Online/QPGI_Online.h"

#include "QPUtil.h"
UQPGI_Online* UQPGI_Online::qp_staticObject = nullptr;
bool UQPGI_Online::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGI_Online::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());

	QP_InitStaticObject();

	qp_onlineData = UQPGIM_BaseData::qp_staticObject->QP_GetOnlineData();
	qp_onlineData->QP_LoadData("UQPGI_Online");
	//qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_GetUQPData("_");
	//qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData("qp_sending")->QP_SetIsSave(EQPDataKeyType::FNAME, EQPDataValueType::UQPDATA, false);
	
}
void UQPGI_Online::QP_InitStaticObject() {
	UQPGI_Online::qp_staticObject = this;
}
void UQPGI_Online::Deinitialize()
{

	Super::Deinitialize();

	qp_staticObject = nullptr;
}
void UQPGI_Online::QP_StartLogout() {
	
	if (qp_identityInterface.IsValid())
	{
		qp_identityInterface->Logout(0);
	}
	
}
void UQPGI_Online::QP_Init() {
	if (qp_isInit) {
		return;
	}
	UWorld* w = GetWorld();
	if (!w) {
		return;
	}
	
	qp_isInit = true;
	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", false);
	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isQueryAchievements", false);
	//if (!qp_userInterface) {
	qp_userInterface = Online::GetUserInterface(w);
	if (qp_userInterface.IsValid())
	{
		qp_userInterface->AddOnQueryUserInfoCompleteDelegate_Handle(0,FOnQueryUserInfoCompleteDelegate::CreateUObject(this,&UQPGI_Online::QP_QueryUserInfo));
	}
	//}
	
	
	qp_identityInterface = Online::GetIdentityInterface(w);
	if (qp_identityInterface.IsValid())
	{
		qp_identityInterface->AddOnLogoutCompleteDelegate_Handle(0,FOnLogoutCompleteDelegate::CreateUObject(this, &UQPGI_Online::QP_LogoutComplete));
		qp_identityInterface->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &UQPGI_Online::QP_LoginComplete));
	}
	qp_achievements = Online::GetAchievementsInterface(w);
	if (qp_achievements.IsValid()) {

	}
	qp_statsInterface = Online::GetStatsInterface(w);

	/*if (QP_GetPlatform() == "Steam") {
		QP_StartLogin("");
	}
	else if (QP_GetPlatform() == "EOS") {
	}*/
		QP_StartLogin();
	//QP_LoadUserData();
	//QP_QueryAchievements();
	
		
	
}
void UQPGI_Online::QP_ShowStore(bool addToCart) {
	FString SteamAppID;
	GConfig->GetString(
		TEXT("OnlineSubsystemSteam"),
		TEXT("SteamAppId"),
		SteamAppID,
		GEngineIni
	);
	//GConfig->GetString(TEXT("OnlineSubsystem"), TEXT("SteamDevAppId"), PlatformService, GEngineIni);
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (!OnlineSub)
	{
		UQPUtil::QP_LOG("No OnlineSubsystem");
		return;
	}

	IOnlineExternalUIPtr ExternalUI = OnlineSub->GetExternalUIInterface();
	if (!ExternalUI.IsValid())
	{
		UQPUtil::QP_LOG("No External UI Interface");
		return;
	}
	//UQPUtil::QP_LOG( SteamAppID);

	FShowStoreParams s;
	s.bAddToCart = addToCart;
	s.ProductId = SteamAppID;
	ExternalUI->ShowStoreUI(0,s);
}
void UQPGI_Online::QP_QueryUserInfo(int32 LocalUserNum, bool bWasSuccessful, const TArray<TSharedRef<const FUniqueNetId>>& UserIds, const FString& ErrorStr) {

	if (bWasSuccessful)
	{
		/*FUniqueNetIdPtr qp_userId = qp_identityInterface->GetUniquePlayerId(0);
		if (qp_userInterface.IsValid() && qp_identityInterface.IsValid() && qp_userId.IsValid())
		{
			TSharedPtr<const FOnlineUser> UserInfo = qp_userInterface->GetUserInfo(LocalUserNum, *qp_userId);
			if (UserInfo.IsValid())
			{
				UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_AddFString("userName", UserInfo->GetDisplayName());
			}
		}*/
	}
	else
	{

	}
}
void UQPGI_Online::QP_LoadUserData() 
{

	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_AddFString("userName", *(qp_identityInterface->GetPlayerNickname(0)));

	qp_userId = qp_identityInterface->GetUniquePlayerId(0);
	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", qp_userId.IsValid());
	/*if (qp_userInterface.IsValid() && qp_identityInterface.IsValid() && qp_userId.IsValid())
	{
		TArray<TSharedRef<const FUniqueNetId>> Users;
		Users.Add(qp_userId.ToSharedRef());
		qp_userInterface->QueryUserInfo(0, Users);
		;
	}*/
}
void UQPGI_Online::QP_LogInUI() {
	if (qp_isLongining) {
		return;
	}
	qp_isLongining = true;
	UQPUtil::QP_UpdateMouse(true);
	Online::GetExternalUIInterface(GetWorld())->ShowLoginUI(0, true, true, FOnLoginUIClosedDelegate::CreateLambda(
		[this](TSharedPtr<const FUniqueNetId> UniqueId, const int ControllerIndex, const FOnlineError& Result) {
			UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", Result.WasSuccessful());
			qp_isLongining = false;
			qp_isSwitching = false;
			UQPUtil::QP_UpdateMouse(false);
			if (Result.WasSuccessful())
			{
				QP_QueryAllData();
			}
		}));
}
void UQPGI_Online::QP_LogoutComplete(int32 UserNum, bool bWasSuccessful) {
	if (bWasSuccessful)
	{
		UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", false);
		QP_LogInUI();
	}
}
void UQPGI_Online::QP_StartSwitchAccounts() {
	if (qp_isSwitching) {
		return;
	}
	
	if (qp_identityInterface.IsValid())
	{
		qp_isSwitching = true;
		qp_identityInterface->Logout(0);
	}
	
}

void UQPGI_Online::QP_LoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error) {
	qp_isLongining = false;
	if (!bWasSuccessful) {

		if (!UQPGIM_BaseData::qp_staticObject) {
			return;
		}
		if (qp_loginType == "persistentauth") {
			QP_StartLogin("accountportal");
		}
		else {
			QP_LogInUI();
		}
	}
	else {
		UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isLongin", true);
		QP_QueryAllData();
	}
}

void UQPGI_Online::QP_StartLogin(FString loginType) {
	
	if (qp_isLongining) 
	{
		return;
	}
	if (qp_identityInterface.IsValid())
	{	
		qp_isLongining = true;
		qp_loginType = loginType;
		qp_identityInterface->Login(0, FOnlineAccountCredentials(qp_loginType, TEXT(""), TEXT("")));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("IdentityInterface error！"));
	}
	
}
void UQPGI_Online::QP_UploadStats(FName statsId, float num) {

	if (statsId.IsNone()) {
		return;
	}

	if (FMath::IsNearlyEqual(qp_onlineData->QP_GetUQPData("Stats")->QP_Getdouble(statsId),num)) {

		return;
	}

	qp_onlineData->QP_GetUQPData("Stats")->QP_Adddouble(statsId,num);
	qp_onlineData->QP_SaveData("UQPGI_Online");

	if (qp_statsInterface.IsValid() && qp_userId.IsValid()) {
		FUniqueNetIdRef UserId = qp_userId.ToSharedRef();
		FOnlineStatsUserUpdatedStats st(UserId);

		st.Stats.Add(
			statsId.ToString(),
			FOnlineStatUpdate(
				FVariantData(num),
				FOnlineStatUpdate::EOnlineStatModificationType::Unknown
			)
		);
		TArray<FOnlineStatsUserUpdatedStats> s;
		s.Add(st);
		
		qp_statsInterface->UpdateStats(
			UserId,
			s,
			FOnlineStatsUpdateStatsComplete::CreateLambda([](const FOnlineError& Result)
				{

				})
		);
	}
}
void UQPGI_Online::QP_QueryAllData() {
	QP_LoadUserData();
	QP_QueryAchievements();
	QP_QueryStats();
}
void UQPGI_Online::QP_QueryStats() {
	if (qp_statsInterface.IsValid() && qp_userId.IsValid())
	{
		FUniqueNetIdRef UserId = qp_userId.ToSharedRef();
		
		qp_statsInterface->QueryStats(UserId, UserId, FOnlineStatsQueryUserStatsComplete::CreateLambda(
			[this, UserId](const FOnlineError& ResultState, const TSharedPtr<const FOnlineStatsUserStats>& QueriedStats)
			{
				if (ResultState.bSucceeded)
				{
					double num = 0;
					TArray<FOnlineStatsUserUpdatedStats> s;

					for (auto v : QueriedStats.Get()->Stats)
					{
						FString StatName = v.Key;
						const FVariantData& StatValue = v.Value;

						switch (StatValue.GetType())
						{
							case EOnlineKeyValuePairDataType::Int32:
							{
								int32 numV;
								StatValue.GetValue(numV);
								num = numV;
								break;
							}
							case EOnlineKeyValuePairDataType::UInt32:
							{
								uint32 numV;
								StatValue.GetValue(numV);
								num = numV;

								break;
							}
							case EOnlineKeyValuePairDataType::Int64:
							{
								int64 numV;
								StatValue.GetValue(numV);
								num = numV;
								break;
							}
							case EOnlineKeyValuePairDataType::UInt64:
							{
								uint64 numV;
								StatValue.GetValue(numV);
								num = numV;
								break;
							}
							case EOnlineKeyValuePairDataType::Float: {
								float numV;
								StatValue.GetValue(numV);
								num = numV;
								break;
							}
							
							case EOnlineKeyValuePairDataType::Double:
							{
								double numV;
								StatValue.GetValue(numV);
								num = numV;
								break;
							}
							default:{
								num = 0;
								break;
							}
						}
						
						if (!FMath::IsNearlyEqual(qp_onlineData->QP_GetUQPData("Stats")->QP_Getdouble(*StatName),num)) {

							FOnlineStatsUserUpdatedStats st(UserId);

							st.Stats.Add(
								StatName,
								FOnlineStatUpdate(
									FVariantData(num),
									FOnlineStatUpdate::EOnlineStatModificationType::Unknown
								)
							);
							s.Add(st);
						}

					}
					if (s.Num() > 0) {
						qp_statsInterface->UpdateStats(
							UserId,
							s,
							FOnlineStatsUpdateStatsComplete::CreateLambda([](const FOnlineError& Result)
								{

								})
						);
					}
					
				}
			}
		));
	}
}
void UQPGI_Online::QP_QueryAchievements() {
		
	
	if (qp_achievements.IsValid()&&qp_userId.IsValid())
	{

		
		qp_achievements->QueryAchievements(*qp_userId, FOnQueryAchievementsCompleteDelegate::CreateLambda(
				[this](const FUniqueNetId& QueriedId, const bool bSuccess)
				{
					UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isQueryAchievements", bSuccess);
					if (bSuccess) {
						TArray<FOnlineAchievement> PlayerAchievements;

						qp_achievements->GetCachedAchievements(*qp_userId, PlayerAchievements);

						FOnlineAchievementsWritePtr WriteObject = MakeShareable(new FOnlineAchievementsWrite());


						FOnlineAchievementsWriteRef WriteRef = WriteObject.ToSharedRef();
						bool isSend = false;
						for (const FOnlineAchievement& Achievement : PlayerAchievements)
						{
							if (Achievement.Progress < 0.9)
							{
								if (qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData((*Achievement.Id))->QP_GetboolExI(0)) {
									WriteObject->SetFloatStat(Achievement.Id, 100);
									isSend = true;
								}
							}
						}
						if (isSend) {
							qp_achievements->WriteAchievements(*qp_userId, WriteRef);
						}
						/*Achievements->WriteAchievements(*UserId, WriteRef,
							FOnAchievementsWrittenDelegate::CreateLambda([](const FUniqueNetId& PlayerId, bool bWriteSuccess)
								{
								}));*/
					}

				}));
		
	}
	else {
		UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addbool("isQueryAchievements", false);
	}
}
void UQPGI_Online::QP_AddAchievement(FName qp_AchievementId, int32 qp_playerId, float num) {
	if (qp_AchievementId.IsNone()) {
		return;
	}

	if (qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_GetboolExI(qp_playerId)) {

		return;
	}

	qp_onlineData->QP_GetUQPData("Achievement")->QP_GetUQPData(qp_AchievementId)->QP_AddboolExI(qp_playerId, true);
	qp_onlineData->QP_SaveData("UQPGI_Online");

	if (qp_identityInterface.IsValid() && qp_achievements.IsValid() && qp_userId.IsValid())
	{
			
			FOnlineAchievement Achievement;
			if (qp_achievements->GetCachedAchievement(*qp_userId, qp_AchievementId.ToString(), Achievement) == EOnlineCachedResult::Success)
			{
				if (Achievement.Progress>0)
				{
					return;
				}
				
			}

			FOnlineAchievementsWritePtr WriteObject = MakeShareable(new FOnlineAchievementsWrite());
			WriteObject->SetFloatStat(qp_AchievementId.ToString(), num);

			FOnlineAchievementsWriteRef WriteRef = WriteObject.ToSharedRef();
			qp_achievements->WriteAchievements(*qp_userId, WriteRef);

			/*Achievements->WriteAchievements(*UserId, WriteRef,
				FOnAchievementsWrittenDelegate::CreateLambda([this, qp_AchievementId, num, qp_playerId](const FUniqueNetId& PlayerId, bool bWriteSuccess)
					{

						if (num == 100 && bWriteSuccess) {


						}
						else {

						}
					}));*/
					
			
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


