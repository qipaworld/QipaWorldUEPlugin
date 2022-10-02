// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/QPGIM_Map.h"

#include "Setting/QPDeveloperSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"

//#include <MoviePlayer/Public/MoviePlayer.h>
//#include "Data/QPData.h"


UQPGIM_Map* UQPGIM_Map::QP_UQPGIM_Map = nullptr;


bool UQPGIM_Map::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Map::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGIM_Map = this;

	qp_actionInfo.CallbackTarget = this;
	qp_actionInfo.ExecutionFunction = "QP_LoadMapEnd";
	qp_actionInfo.UUID = UQPDeveloperSettings::QP_GET()->QP_UUID["qp_loadMap"];
	qp_actionInfo.Linkage = 0;

	qp_loadingMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultLoadingMap;
	//qp_loadingMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Map::Deinitialize()
{
	Super::Deinitialize();
}

void UQPGIM_Map::QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation)
{
	qp_isLoadMap = false;
	ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), MapName, Location, Rotation, qp_isLoadMap);
}
void UQPGIM_Map::QP_OpenMap(const FString LevelName)
{
	//qp_loadMapName = LevelName;
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));

}
void UQPGIM_Map::QP_LoadingAndOpenMap(const FString MapName)
{
	qp_readyOpenMapName = MapName;
	QP_LoadMap(qp_loadingMapName, FVector::ZeroVector, FRotator::ZeroRotator);
}

void UQPGIM_Map::QP_OpenReadyMap()
{
	QP_OpenMap(qp_readyOpenMapName);
}

void UQPGIM_Map::QP_LoadSubMap(const FString MapName)
{
	qp_isLoadSubMap = false;
	UGameplayStatics::LoadStreamLevel(GetWorld(), FName(MapName), true, false, qp_actionInfo);
}
void UQPGIM_Map::QP_LoadMapEnd()
{
	qp_isLoadSubMap = true;
}
