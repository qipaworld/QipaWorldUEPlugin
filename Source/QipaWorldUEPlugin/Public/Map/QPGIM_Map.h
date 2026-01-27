// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "World/QPWorldData.h"

#include "QPGIM_Map.generated.h"

UENUM(BlueprintType)
enum class EQPSunType : uint8 
{
	NONE = 0        UMETA(DisplayName = "none"),
	MORNING = 1        UMETA(DisplayName = "morning"),
	NOON = 1<<1      UMETA(DisplayName = "noon"),
	AFTERNOON = 1 << 2       UMETA(DisplayName = "afternoon"),
	NIGHT = 1 << 3    UMETA(DisplayName = "night"), 
	MIDNIGHT = 1 << 4       UMETA(DisplayName = "midnight"),
	AFTERMIDNIGHT = 1 << 5      UMETA(DisplayName = "after midnight"),
};
//FORCEINLINE EQPSunType operator|(EQPSunType A, EQPSunType B)
//{
//	return static_cast<EQPSunType>(
//		static_cast<uint8>(A) | static_cast<uint8>(B)
//		);
//}
ENUM_CLASS_FLAGS(EQPSunType)

//FORCEINLINE bool operator&(EQPSunType A, EQPSunType B)
//{
//	return static_cast<uint8>(A) & static_cast<uint8>(B);
//}
//USTRUCT(BlueprintType)
//struct FQPSunTime 
//{
//	GENERATED_BODY()
//public:
//
//};
/**
 * 地图管理类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Map : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Map* qp_staticObject;
	virtual void QP_InitStaticObject();

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	// range 0 - 1   sun = 360  0 = 0  360 = 1  0.25 = noon  0.75 = midnaght
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	float qp_mapSunTime = 0.5;
	// range 0 - 1   0:00  and 23:59 = 0  12:00 = 1
	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	//float qp_mapTimeEx = 0.5;

	// next SunType num
	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	//float qp_mapTimeStart = 0.5;
	
	//UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	//float qp_mapTimeNext = 0.5;
	// 0 - 1,  EQPSunType to next EQPSunType,  noon to afternoon time 
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	float qp_mapSunTimeEx = 0.5;

	// 0 - 1
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	float qp_mapSunTemperature = 0.5;

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	float qp_mapTemperature = 0.5;

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	EQPSunType qp_mapSunType = EQPSunType::MORNING;

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	class UQPData* qp_mapData;
	/** 是否加载完成*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	bool qp_isLoadMap = false;

	/** 子地图是否加载完成*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	bool qp_isLoadSubMap = false;

	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPMap")
	UQPWorldData* qp_worldBaseData = nullptr;
	/** 这个是准备打开的地图名字*/
	FName qp_readyOpenMapName;
	/**带进度条地图的名字*/
	//FString qp_loadingMapName;

	/**子地图加载的action*/
	FLatentActionInfo qp_actionInfo;

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	FORCEINLINE bool QP_IsInSunType(EQPSunType A) {
		return static_cast<uint8>(A)& static_cast<uint8>(qp_mapSunType);
	}

	/** 加载新地图，并且保持原来的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadMap(const FString& MapName, const FVector& Location, const FRotator& Rotation);

	/** 直接切换地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_OpenMap(FName MapName);

	/** 切换地图的时候加个进度条*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadingAndOpenMap(FName MapName);
	/** 打开准备加载的地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_OpenReadyMap();

	/** 获取地图数据*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	class UQPData* QP_GetMapData();
	/** 加载子地图*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	void QP_LoadSubMap(FName MapName);

	/*UFUNCTION(BlueprintCallable, Category = "QipaWorld|Map")*/
	void QP_LoadMapEnd();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMap")
	UQPWorldData* QP_GetMapWorldData();
	// v = 0 - 1
	void QP_SetSunRotation(float v);
private:
	

};
