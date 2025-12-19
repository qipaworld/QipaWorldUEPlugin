// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_PlayerData : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	

public:
	static UQPGIM_PlayerData* qp_staticObject;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|PlayerData")
	class UQPData* qp_localPlayerData;
	
	FName qp_saveLocalPlayerDataName = "qp_saveLocalPlayerDataName";

	class UQPData* qp_localPlayerSaveData;
	virtual void QP_LoadLocalData();
	virtual void QP_SaveLocalData();

	virtual void QP_InitStaticObject();

	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|PlayerData")
	class UQPData* QP_GetLocalPlayerData();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|PlayerData")
	class UQPData* QP_GetLocalPlayerSaveData();
	
};
