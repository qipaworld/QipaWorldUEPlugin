// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/QPGIM_Actor.h"
#include "Map/QPGIM_Map.h"
#include "Data/QPData.h"

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
	Collection.InitializeDependency(UQPGIM_Map::StaticClass());
	UQPGIM_Map::qp_staticObject->QP_GetMapData()->qp_dataDelegate.AddUObject(this, &UQPGIM_Actor::QP_BindMapData);
	qp_staticObject = this;

}
void UQPGIM_Actor::QP_BindMapData(UQPData* data)
{

	 if (data->QP_IsChange<FName, FName>("baseLevelName", EQPDataValueType::FNAME)) {
		 qp_actorData.Reset();
		}

}
void UQPGIM_Actor::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;

}

void UQPGIM_Actor::QP_AddActor(FString key, AActor* actor, bool ishid)
{
	if (!qp_actorData.Contains(key)) {
		qp_actorData.Emplace(key, TArray<AActor*>());
	}
	qp_actorData[key].Add(actor);
	if (ishid) {
		actor->SetActorHiddenInGame(true);
		actor->SetActorEnableCollision(false);    
		actor->SetActorTickEnabled(false);        
	}
}


AActor* UQPGIM_Actor::QP_PopActor(FString key, bool isshow)
{
	AActor* actor = nullptr;
	if (qp_actorData.Contains(key)) {
		if (qp_actorData[key].Num() > 0) {
			actor = qp_actorData[key].Pop();
			if (isshow) {
				actor->SetActorHiddenInGame(false);
				actor->SetActorEnableCollision(true);   
				actor->SetActorTickEnabled(true);        
			}
			//actor->SetActorHiddenInGame(false);
			//actor->RemoveFromRoot();
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