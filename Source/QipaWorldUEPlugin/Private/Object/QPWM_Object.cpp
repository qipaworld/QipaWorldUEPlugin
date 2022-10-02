// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/QPWM_Object.h"
// #include "Data/QPGIM_Data.h"
//#include <Engine/StreamableManager.h>
//#include <Engine/ObjectLibrary.h>


UQPWM_Object* UQPWM_Object::QP_UQPWM_Object = nullptr;


bool UQPWM_Object::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPWM_Object::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPWM_Object = this;
	
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPWM_Object::Deinitialize()
{
	Super::Deinitialize();
}

void UQPWM_Object::QP_CollectObject(FString key, UObject* obj)
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

UObject* UQPWM_Object::QP_GetObject(FString key)
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
//void UQPWM_Object::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UObjectLibrary* objLib = UObjectLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUObject(this, &UQPWM_Object::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWM_Object::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftObjectPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUObject(this, &UQPWM_Object::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWM_Object::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftObjectPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUObject(this, &UQPWM_Object::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPWM_Object::QP_RequestAsyncLoadDeferred()
//{
//}

