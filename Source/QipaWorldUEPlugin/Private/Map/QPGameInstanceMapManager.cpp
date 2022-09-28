// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/QPGameInstanceMapManager.h"
#include "Setting/QPDeveloperSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"

//#include <MoviePlayer/Public/MoviePlayer.h>
//#include "Data/QPData.h"


UQPGameInstanceMapManager* UQPGameInstanceMapManager::QP_UQPGameInstanceMapManager = nullptr;


bool UQPGameInstanceMapManager::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGameInstanceMapManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGameInstanceMapManager = this;

	qp_actionInfo.CallbackTarget = this;
	qp_actionInfo.ExecutionFunction = "QP_LoadMapEnd";
	qp_actionInfo.UUID = UQPDeveloperSettings::QP_GET()->QP_UUID["qp_loadMap"];
	qp_actionInfo.Linkage = 0;

	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGameInstanceMapManager::Deinitialize()
{
	Super::Deinitialize();
}

void UQPGameInstanceMapManager::QP_LoadMap(const FString MapName, const FVector Location, const FRotator Rotation)
{
	qp_isLoadMap = false;
	ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), MapName, Location, Rotation, qp_isLoadMap);
}
void UQPGameInstanceMapManager::QP_OpenMap(const FString LevelName)
{
	//qp_loadMapName = LevelName;
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));

}
void UQPGameInstanceMapManager::QP_LoadSubMap(const FString MapName)
{
	qp_isLoadSubMap = false;
	UGameplayStatics::LoadStreamLevel(GetWorld(), FName(MapName), true, false, qp_actionInfo);
}
void UQPGameInstanceMapManager::QP_LoadMapEnd()
{
	qp_isLoadSubMap = true;
}

