// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/QPWM_Actor.h"
#include "Actor/QPActor.h"
// #include "Data/QPGIM_Data.h"
//#include <Engine/StreamableManager.h>
//#include <Engine/ActorLibrary.h>


UQPWM_Actor* UQPWM_Actor::QP_UQPWM_Actor = nullptr;


bool UQPWM_Actor::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPWM_Actor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPWM_Actor = this;
	
	//LoadYaml("");
	//qp_gameQPdataBase = NewActor<UQPData>();
}

void UQPWM_Actor::Deinitialize()
{
	Super::Deinitialize();
}

void UQPWM_Actor::QP_CollectActor(FString key, AQPActor* actor)
{	
	if (qp_actorData.Contains(key)) {
		qp_actorData[key].Add(actor);
	}
	else {
		TArray<AQPActor*> array;
		array.Add(actor);
		qp_actorData.Add(key, array);
	}
	actor->AddToRoot();
}

AQPActor* UQPWM_Actor::QP_GetActor(FString key)
{
	AQPActor* actor = nullptr;
	if (qp_actorData.Contains(key)) {
		TArray<AQPActor*> array = qp_actorData[key];
		int num = array.Num()-1;
		if (num >= 0) {
			actor = array[num];
			array.RemoveAt(num);
		}
		//qp_objData[key].Add(obj);
	}
	return actor;
}
//
//void UQPWM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UActorLibrary* objLib = UActorLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUActor(this, &UQPWM_Actor::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftActorPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPWM_Actor::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPWM_Actor::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftActorPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPWM_Actor::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPWM_Actor::QP_RequestAsyncLoadDeferred()
//{
//}

