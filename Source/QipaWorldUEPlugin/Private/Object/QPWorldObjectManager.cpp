// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/QPWorldObjectManager.h"
#include "Data/QPGameInstanceDataManager.h"
//#include <Engine/StreamableManager.h>
//#include <Engine/ObjectLibrary.h>


UQPWorldObjectManager* UQPWorldObjectManager::QP_UQPWorldObjectManager = nullptr;


bool UQPWorldObjectManager::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPWorldObjectManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPWorldObjectManager = this;
	
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPWorldObjectManager::Deinitialize()
{
	Super::Deinitialize();
}

void UQPWorldObjectManager::QP_CollectObject(FString key, UObject* obj)
{	
	if (qp_objData.Contains(key)) {
		qp_objData[key].Add(obj);
	}
	else {
		TArray<UObject*> array;
		array.Add(obj);
		qp_objData.Add(key, array);
	}
	obj->AddToRoot();	
}

UObject* UQPWorldObjectManager::QP_GetObject(FString key)
{
	UObject* obj = nullptr;
	if (qp_objData.Contains(key)) {
		TArray<UObject*> array = qp_objData[key];
		int num = array.Num()-1;
		if (num >= 0) {
			obj = array[num];
			array.RemoveAt(num);
		}
		//qp_objData[key].Add(obj);
	}
	return obj;
}
//
//void UQPWorldObjectManager::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UObjectLibrary* objLib = UObjectLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUObject(this, &UQPWorldObjectManager::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWorldObjectManager::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftObjectPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUObject(this, &UQPWorldObjectManager::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWorldObjectManager::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftObjectPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUObject(this, &UQPWorldObjectManager::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPWorldObjectManager::QP_RequestAsyncLoadDeferred()
//{
//}
