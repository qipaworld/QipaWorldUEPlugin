// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/QPGIM_Actor.h"

#include "QPUtil.h"

UQPGIM_Actor* UQPGIM_Actor::qp_staticObject = nullptr;


bool UQPGIM_Actor::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Actor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	qp_staticObject = this;

	//LoadYaml("");
	//qp_gameQPdataBase = NewActor<UQPData>();
}

void UQPGIM_Actor::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;

}

void UQPGIM_Actor::QP_CollectActor(FString key, AActor* actor)
{
	if (qp_actorData.Contains(key)) {
		qp_actorData[key].Add(actor);
	}
	else {
		TArray<AActor*> array;
		array.Add(actor);
		qp_actorData.Add(key, array);
	}
	actor->AddToRoot();
}

AActor* UQPGIM_Actor::QP_GetActor(FString key)
{
	AActor* actor = nullptr;
	if (qp_actorData.Contains(key)) {
		TArray<AActor*> array = qp_actorData[key];
		int num = array.Num() - 1;
		if (num >= 0) {
			actor = array[num];
			array.RemoveAt(num);
		}
		//qp_objData[key].Add(obj);
	}
	return actor;
}
//
//void UQPGIM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UActorLibrary* objLib = UActorLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUActor(this, &UQPGIM_Actor::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftActorPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Actor::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftActorPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Actor::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPGIM_Actor::QP_RequestAsyncLoadDeferred()
//{
//}