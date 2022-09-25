// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/QPGameInstanceLoadAssetsManager.h"
#include "Data/QPGameInstanceDataManager.h"
//#include "Node.h"
//#include "Parsing.h"


UQPGameInstanceLoadAssetsManager* UQPGameInstanceLoadAssetsManager::QP_UQPGameInstanceLoadAssetsManager = nullptr;


bool UQPGameInstanceLoadAssetsManager::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGameInstanceLoadAssetsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGameInstanceLoadAssetsManager = this;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPGameInstanceLoadAssetsManager::Deinitialize()
{
	Super::Deinitialize();
}
//
//UQPData* UQPGameInstanceLoadAssetsManager::LoadYaml(FString key, UQPData* data)
//{
//	FYamlNode config;
//
//	bool b = UYamlParsing::LoadYamlFromFile(FPaths::ProjectDir() + "Content/YamlDataFiles/VersionData.yaml", config);
//	//config["iosGameVersion"]
//	//if (config["iosGameVersion"]) {
//		//UE_LOG(LogTemp, Waring, TEXT(""));
//	//FString ss = ;
//	UE_LOG(LogTemp, Warning, TEXT("ProjectDir_%s"), *(FPaths::ProjectDir()));
//	UE_LOG(LogTemp, Warning, TEXT("ProjectContentDir_%s"), *(FPaths::ProjectContentDir()));
//	UE_LOG(LogTemp, Warning, TEXT("ProjectPluginsDir_%s"), *(FPaths::ProjectPluginsDir()));
//	UE_LOG(LogTemp, Warning, TEXT("EnginePluginsDir_%s"), *(FPaths::EnginePluginsDir()));
//	UE_LOG(LogTemp, Warning, TEXT("EngineContentDir_%s"), *(FPaths::EngineContentDir()));
//	UE_LOG(LogTemp, Warning, TEXT("GetProjectFilePath_%s"), *(FPaths::GetProjectFilePath()));
//	UE_LOG(LogTemp, Warning, TEXT("LaunchDir_%s"), *(FPaths::LaunchDir()));
//	UE_LOG(LogTemp, Warning, TEXT("GetProjectFilePath_%s"), *(FPaths::GetProjectFilePath()));
//	
//	if (b) {
//		UE_LOG(LogTemp, Warning, TEXT("0iosGameVersion_%s"), *(config["iosGameVersion"].Scalar()));
//
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("0iosGameVersion____________"));
//
//	}
//
//
//	
//	return nullptr;
//}
