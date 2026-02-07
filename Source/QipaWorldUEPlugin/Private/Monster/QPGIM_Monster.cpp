// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/QPGIM_Monster.h"
#include "Data/QPGIM_BaseData.h"
#include "Character/QPGIM_Character.h"

#include "Data/QPData.h"
#include "Actor/QPGIM_Actor.h"
#include "QPUtil.h"

UQPGIM_Monster* UQPGIM_Monster::qp_staticObject = nullptr;


bool UQPGIM_Monster::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Monster::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());
	//UQPGIM_Map::qp_staticObject->QP_GetMapData()->qp_dataDelegate.AddUObject(this, &UQPGIM_Monster::QP_BindMapData);
	QP_InitStaticObject();

	qp_defaultMonsters = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMonsters.LoadSynchronous();
	qp_defaultMonsters->AddToRoot();
}
AActor* UQPGIM_Monster::QP_GetDefaultMonster(FName n, FTransform T) {
	if (IsValid(qp_defaultMonsters) && qp_defaultMonsters->qp_monsterMap.Contains(n)) {

		FActorSpawnParameters qp_spawnP;
		qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		return GetWorld()->SpawnActor<AActor>(qp_defaultMonsters->qp_monsterMap[n], T, qp_spawnP);
	}
	return nullptr;
}
void UQPGIM_Monster::QP_InitStaticObject() {
	UQPGIM_Monster::qp_staticObject = this;
}

void UQPGIM_Monster::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;

}

void UQPGIM_Monster::QP_AddMonster(const FName& key, AActor* actor, bool ishid)
{
	actor->Destroy();
	//UQPGIM_Actor::qp_staticObject->QP_AddActor(key,actor,ishid);
}


AActor* UQPGIM_Monster::QP_GetMonster(const FName& key, FTransform t, bool isshow)
{
	/*AActor* actor = UQPGIM_Actor::qp_staticObject->QP_PopActor(key,t,isshow);
	if (!actor) {
		actor = QP_GetDefaultMonster(key,t);
	}*/
	return QP_GetDefaultMonster(key, t);
}
UQPDA_Character* UQPGIM_Monster::QP_GetMonsterData(const FName& key)
{
	return LoadObject<UQPDA_Character>(nullptr, *((UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultCharacterDataPath.Path) + "/" + key.ToString() + "." + key.ToString()));
}
//
//void UQPGIM_Monster::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UActorLibrary* objLib = UActorLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUActor(this, &UQPGIM_Monster::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Monster::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftActorPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Monster::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Monster::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftActorPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Monster::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPGIM_Monster::QP_RequestAsyncLoadDeferred()
//{
//}