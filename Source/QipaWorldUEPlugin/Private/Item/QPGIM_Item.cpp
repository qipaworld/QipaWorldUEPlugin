// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/QPGIM_Item.h"
#include "Data/QPGIM_BaseData.h"

#include "Data/QPData.h"
#include "Actor/QPGIM_Actor.h"
#include "QPUtil.h"
#include "Monster/QPMonster.h"
#include "Item/QPA_Item.h"
UQPGIM_Item* UQPGIM_Item::qp_staticObject = nullptr;


bool UQPGIM_Item::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Item::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_BaseData::StaticClass());
	//UQPGIM_Map::qp_staticObject->QP_GetMapData()->qp_dataDelegate.AddUObject(this, &UQPGIM_Item::QP_BindMapData);
	QP_InitStaticObject();

	qp_defaultItemActors = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultItems.LoadSynchronous();
	qp_defaultItemActors->AddToRoot();
}
AActor* UQPGIM_Item::QP_GetDefaultItemActor(FName n,FTransform T) {
	if (IsValid(qp_defaultItemActors) && qp_defaultItemActors->qp_itemMap.Contains(n)) {

		FActorSpawnParameters qp_spawnP;
		qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		return GetWorld()->SpawnActor<AActor>(qp_defaultItemActors->qp_itemMap[n], T, qp_spawnP);
	}
	return nullptr;
}
void UQPGIM_Item::QP_InitStaticObject() {
	UQPGIM_Item::qp_staticObject = this;
}

void UQPGIM_Item::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;

}

void UQPGIM_Item::QP_AddItemActor(const FName& key, AActor* actor, bool ishid)
{
	UQPGIM_Actor::qp_staticObject->QP_AddActor(key,actor,ishid);
}


AActor* UQPGIM_Item::QP_GetItemActor(const FName& key, FTransform t, bool isshow)
{
	AActor* actor = UQPGIM_Actor::qp_staticObject->QP_PopActor(key,t,isshow);
	if (!actor) {
		actor = QP_GetDefaultItemActor(key,t);
	}
	return actor;
}
UQPDA_Item* UQPGIM_Item::QP_GetItemData(const FName& key)
{
	return LoadObject<UQPDA_Item>(nullptr, *((UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultItemDataPath.Path) + "/" + key.ToString() + "." + key.ToString()));
}
//
//void UQPGIM_Item::QP_RequestAsyncLoad(UClass* InBaseClass, FString key, UQPData* data)
//{
//	UActorLibrary* objLib = UActorLibrary::CreateLibrary(InBaseClass, false, false);
//	qp_streamableManager->RequestAsyncLoad(objLib, FStreamableDelegate::CreateUActor(this, &UQPGIM_Item::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Item::QP_RequestAsyncLoad(UClass* InBaseClass, FSoftActorPath& keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Item::QP_RequestAsyncLoadDeferred));
//}
//
//void UQPGIM_Item::QP_RequestAsyncLoad(UClass* InBaseClass, TArray<FSoftActorPath> keys, UQPData* data)
//{
//	qp_streamableManager->RequestAsyncLoad(keys, FStreamableDelegate::CreateUActor(this, &UQPGIM_Item::QP_RequestAsyncLoadDeferred));
//
//}
//
//void UQPGIM_Item::QP_RequestAsyncLoadDeferred()
//{
//}



//{
//	UGameplayEffect* GE = NewObject<UGameplayEffect>(Outer);
//	GE->DurationPolicy = EGameplayEffectDurationType::Instant;
//
//	for (TFieldIterator<FProperty> It(SetClass->GetClass()); It; ++It)
//	{
//		FProperty* AttrProp = *It;
//
//		// 只处理 AttributeSet 的属性
//		if (!AttrProp->IsA<FStructProperty>()) continue;
//
//		FStructProperty* StructProp = CastField<FStructProperty>(AttrProp);
//		if (StructProp->Struct != FGameplayAttributeData::StaticStruct()) continue;
//
//		// 数据类里找同名属性
//		FProperty* DataProp = Data->GetClass()->FindPropertyByName(AttrProp->GetFName());
//		if (!DataProp) continue;
//
//		float Value = 0.f;
//		DataProp->CopyCompleteValue(&Value, DataProp->ContainerPtrToValuePtr<void>(Data));
//
//		FGameplayModifierInfo& Mod = GE->Modifiers.AddDefaulted_GetRef();
//		Mod.Attribute = FGameplayAttribute(AttrProp);
//		Mod.ModifierOp = EGameplayModOp::Override;
//		Mod.ModifierMagnitude = FScalableFloat(Value);
//	}
//
//	return GE;
//}

UGameplayEffect* UQPGIM_Item::QP_GetItemGE( FQPItem& n){
	if (n.qp_itemName == "_") {
		return nullptr;
	}
	UGameplayEffect* GE;
	if (qp_itemEffects.Contains(n.qp_itemName)) {
		GE = qp_itemEffects[n.qp_itemName];
		/*FGameplayModifierInfo& Mod = GE->Modifiers.AddDefaulted_GetRef();
		Mod.Attribute = FGameplayAttribute(AttrProp);
		Mod.ModifierOp = EGameplayModOp::AddBase;
		Mod.ModifierMagnitude = FScalableFloat(Value);*/

		//return;
	}
	else {
		GE = NewObject<UGameplayEffect>(nullptr);
		GE->AddToRoot();
		qp_itemEffects.Add(n.qp_itemName, GE);
	}

	int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp() * 1000
		+ FDateTime::UtcNow().GetMillisecond();

	UQPDA_Item*  itemD = QP_GetItemData(n.qp_itemName);
	GE->DurationPolicy = itemD->qp_GEType;

	float timeR = 1 - (TimestampMs - n.qp_createTime) / n.qp_datas["qp_shelfLife"];

	if (timeR < 0.3) {
		n.qp_datas["qp_poison"] = n.qp_datas["qp_poison"] + n.qp_datas["qp_rottenPoison"];
	}

	//FName 
	for (TFieldIterator<FProperty> It(itemD->qp_attributeSet); It; ++It)
	{
		FProperty* AttrProp = *It;
		
		// 只处理 AttributeSet 的属性
		if (!AttrProp->IsA<FStructProperty>()) continue;
		
		FStructProperty* StructProp = CastField<FStructProperty>(AttrProp);
		if (StructProp->Struct != FGameplayAttributeData::StaticStruct()) continue;
		
		// 数据类里找同名属性
		if (! n.qp_datas.Contains(AttrProp->GetFName())) {
			continue;
		}
		//FProperty* DataProp = itemD->GetClass()->FindPropertyByName(AttrProp->GetFName());
		//if (!DataProp) continue;
		//if(n.qp_datas.Contains())
		
		//if( n.qp)
		//float Value = 0.f;
		//DataProp->CopyCompleteValue(&Value, DataProp->ContainerPtrToValuePtr<void>(itemD));
		
		FGameplayModifierInfo& Mod = GE->Modifiers.AddDefaulted_GetRef();
		Mod.Attribute = FGameplayAttribute(AttrProp);
		Mod.ModifierOp = EGameplayModOp::AddBase;
		Mod.ModifierMagnitude = FScalableFloat(n.qp_datas[AttrProp->GetFName()] * timeR);
	}

	return GE;
}

void  UQPGIM_Item::QP_UseItem(TArray<FQPItem>& t, int32 index, AQPMonster* m) {
	if (t[index].qp_itemName != "_") {

		m->qp_abilitySystemComponent->ApplyGameplayEffectToSelf(QP_GetItemGE(t[index]), 1.f, m->qp_abilitySystemComponent->MakeEffectContext());
		t[index].qp_itemName = "_";
	}
}