// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPGIM_BaseData.h"
#include "QPGI_Steam.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGI_Steam : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
public:
	static UQPGI_Steam* qp_staticObject;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/
	UQPData* qp_steamData;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	UFUNCTION(BlueprintCallable)
	void QP_AddAchievement(FName qp_AchievementId,int32 qp_playerId,float num);
};
