// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/QPGIM_Assets.h"
//#include "FileHelpers.h"

UQPGIM_Assets* UQPGIM_Assets::QP_UQPGIM_Assets = nullptr;


bool UQPGIM_Assets::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Assets::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGIM_Assets = this;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPGIM_Assets::Deinitialize()
{
	Super::Deinitialize();
}
//UPackage* UQPGIM_Assets::QP_ReloadPackage(UPackage* InPackageToReload, const uint32 InLoadFlags) {
	//TArray<UPackage*> LoadedPackages;
	//LoadedPackages.Add(InPackageToReload);
	//

	//// Hot-reload the new packages...
	//UEditorLoadingAndSavingUtils::ReloadPackages(LoadedPackages);

//}
