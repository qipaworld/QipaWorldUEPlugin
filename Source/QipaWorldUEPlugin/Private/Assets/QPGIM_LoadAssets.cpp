// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/QPGIM_LoadAssets.h"


UQPGIM_LoadAssets* UQPGIM_LoadAssets::QP_UQPGIM_LoadAssets = nullptr;


bool UQPGIM_LoadAssets::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_LoadAssets::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGIM_LoadAssets = this;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPGIM_LoadAssets::Deinitialize()
{
	Super::Deinitialize();
}
