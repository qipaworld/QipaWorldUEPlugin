// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/QPGIM_Assets.h"
//#include "FileHelpers.h"

UQPGIM_Assets* UQPGIM_Assets::qp_staticObject = nullptr;


bool UQPGIM_Assets::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Assets::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_InitStaticObject();
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}
void UQPGIM_Assets::QP_InitStaticObject() {
	UQPGIM_Assets::qp_staticObject = this;
}
void UQPGIM_Assets::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;
}
//UPackage* UQPGIM_Assets::QP_ReloadPackage(UPackage* InPackageToReload, const uint32 InLoadFlags) {
	//TArray<UPackage*> LoadedPackages;
	//LoadedPackages.Add(InPackageToReload);
	//

	//// Hot-reload the new packages...
	//UEditorLoadingAndSavingUtils::ReloadPackages(LoadedPackages);

//}
