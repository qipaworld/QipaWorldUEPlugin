// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Map.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Map : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Map* QP_UQPGIM_Map;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	/** ¶ÀÁ¢¼ÓÈëµÄ×Ó¹Ø¿¨ÊÇ·ñ¼ÓÔØÍê³É*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadMap = false;

	/** ¶ÀÁ¢¼ÓÈëµÄ×Ó¹Ø¿¨ÊÇ·ñ¼ÓÔØÍê³É*/
	UPROPERTY(BlueprintReadWrite)
	bool qp_isLoadSubMap = false;

	/** ¼´½«¼ÓÔØµÄlevelµÄÃû×Ö¡£*/
	FString qp_readyOpenMapName;

	FString qp_loadingMapName;

	/**¼ÓÔØ³É¹¦ºóµÄ»Øµ÷*/
	FLatentActionInfo qp_actionInfo;

	/** ²»Ð¶ÔØÏÖÔÚµÄlevel£¬Ö±½Ó¼ÓÔØÐÂµÄ*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation);

	/** Õâ¸öÖ±½ÓÇÐ»»µØÍ¼¡£*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenMap(const FString MapName);

	/** Õâ¸ö»á¼ÓÔØloading³¡¾°£¬Ö®ºóÔÚÇÐ»»µØÍ¼¡£*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadingAndOpenMap(const FString MapName);
	/** ÉèÖÃÁËqp_readyOpenMapNameºó£¬¿ÉÒÔÓÃÕâ¸öÇÐ»»µØÍ¼¡£*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_OpenReadyMap();


	/** ¼ÓÔØ×ÓµØÍ¼*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")
	void QP_LoadSubMap(const FString MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();
private:
	

};
