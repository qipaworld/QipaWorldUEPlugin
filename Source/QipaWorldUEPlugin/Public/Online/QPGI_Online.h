// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPGIM_BaseData.h"
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

	UFUNCTION(BlueprintCallable)
	void QP_AddAchievement(FName qp_AchievementId,int32 qp_playerId = 0,float num = 100);

	UFUNCTION(BlueprintCallable)
	void QP_StartLogin();

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
};
