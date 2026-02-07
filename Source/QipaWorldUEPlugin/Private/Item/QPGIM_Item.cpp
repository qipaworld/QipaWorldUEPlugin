// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/QPGIM_Item.h"
#include "Data/QPGIM_BaseData.h"

#include "Data/QPData.h"
#include "Actor/QPGIM_Actor.h"
#include "QPUtil.h"
#include "Monster/QPMonster.h"
#include "QPPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Item/QPDA_ItemTransform.h"
#include "Character/QPGIM_Character.h"
#include "Character/QPCharacter.h"
#include "Data/QPGIM_PlayerData.h"
#include "Character/QPDA_Character.h"
#include "Components/CapsuleComponent.h"
#include "GamePlay/Tags/QPTags.h"
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

	qp_itemQPData = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerItemData();
}
UQPData* UQPGIM_Item::QP_GetItemQPData() {
	return qp_itemQPData;
}

//const FQPItem& UQPGIM_Item::QP_GetPlayerItemData(int index) {
//		return 
//}


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
	actor->Destroy();
	//UQPGIM_Actor::qp_staticObject->QP_AddActor(key,actor,ishid);
}


AActor* UQPGIM_Item::QP_GetItemActor(const FName& key, FTransform t, bool isshow)
{
	//AActor* actor = UQPGIM_Actor::qp_staticObject->QP_PopActor(key,t,isshow);
	//if (!actor) {
		//actor = QP_GetDefaultItemActor(key,t);
	//}
	return QP_GetDefaultItemActor(key, t);
}
UQPDA_Item* UQPGIM_Item::QP_GetItemData(const FName& key)
{
	if (qp_itemDatas.Contains(key)) {
		return qp_itemDatas[key];
	}
	UQPDA_Item* id = LoadObject<UQPDA_Item>(nullptr, *((UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultItemDataPath.Path) + "/" + key.ToString() + "." + key.ToString()));
	id->AddToRoot();
	qp_itemDatas.Add(key, id);
	return id;
}
UTexture2D* UQPGIM_Item::QP_GetItemTexture2D(const FName& key) {
	return QP_GetItemData(key)->qp_showTexture;
}
 FQPItem& UQPGIM_Item::QP_GetPlayerItem(int index) {
	return ((AQPPlayerState*) UGameplayStatics::GetPlayerController(this, 0)->PlayerState)->qp_itemFoods[index];

}
void UQPGIM_Item::QP_UsePlayerItem(int index) {

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	AQPMonster* m = Cast<AQPMonster>(PC->GetPawn());

	//((AQPPlayerState*) PC->PlayerState)->qp_itemFoods[index];

	FQPItem& i =  QP_GetPlayerItem(index);
	if (i.qp_itemName != "_") {
		QP_UseItem(i, m);
		if (QP_GetItemData(i.qp_itemName)->qp_consume) {

			i.qp_itemName = "_";
		}
		qp_itemQPData->QP_Addint32("changeItemIndex", index,EQPDataBroadcastType::SYNC);
	}
}
bool UQPGIM_Item::QP_AddPlayerItem(FQPItem& item) {

	AQPPlayerState* PlayerState = (AQPPlayerState*)UGameplayStatics::GetPlayerController(this, 0)->PlayerState;

	for (size_t i = 0; i < (PlayerState)->qp_itemFoods.Num(); i++)
	{
		
		if ((PlayerState)->qp_itemFoods[i].qp_itemName == "_") {
			(PlayerState)->qp_itemFoods[i] = item;
			
			qp_itemQPData->QP_Addint32("changeItemIndex", i, EQPDataBroadcastType::SYNC);
			PlayerState->QP_SaveItems();
			return true;
		}
	}
	return false;
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
float UQPGIM_Item::QP_GetPlayerItemDataScale(int index) {
	
	return QP_GetPlayerItem(index).QP_GetDataScale();
}
int UQPGIM_Item::QP_GetPlayerItemFreshType(int index) {
	return QP_GetPlayerItem(index).QP_GetFreshType();

}
FName UQPGIM_Item::QP_GetPlayerItemName(int index) {
	return QP_GetPlayerItem(index).qp_itemName;
}
UTexture2D* UQPGIM_Item::QP_GetPlayerItemTexture2D(int index) {
	return QP_GetItemTexture2D(QP_GetPlayerItemName(index));
	//QP_GetPlayerItem(index).get
}
bool UQPGIM_Item::QP_IsPlayerItem(int index) {
	return QP_GetPlayerItemName(index) != "_";
}
bool UQPGIM_Item::QP_CheckPlayerItemShelfLife(int index) {
	//UE_LOG(LogTemp, Warning, TEXT("___!____%d__))))))))"), (index));

	return QP_GetPlayerItem(index).QP_CheckShelfLife();
}
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

	//int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp() ;

	UQPDA_Item*  itemD = QP_GetItemData(n.qp_itemName);
	GE->DurationPolicy = itemD->qp_GEType;

	float timeR = n.QP_GetDataScale();
	int timeT = n.QP_GetFreshType();
	/*(1 - (TimestampMs - n.qp_createTime) / n.qp_datas["qp_shelfLife"]);
	if (timeR >= 0.7) {

	}
	else if (timeR >= 0.3) {
		timeR = 0.7 - (0.7 - timeR) * 0.5;
	}
	else if (timeR > 0) {

		timeR = 0.5 - (0.3 - timeR);

	}*/

	if (timeT == 3) {
		//timeR = 0.2 * (1 + timeR);
		

		n.qp_datas["qp_poison"] = (n.qp_datas["qp_poison"] - n.qp_datas["qp_rottenPoison"] * n.QP_GetDataScaleEX())/ timeR * 2;
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

void  UQPGIM_Item::QP_UseItem(FQPItem& n, AQPMonster* m) {
	if (n.qp_itemName != "_") {

		//m->qp_abilitySystemComponent->ApplyGameplayEffectToSelf(QP_GetItemGE(t), 1.f, m->qp_abilitySystemComponent->MakeEffectContext());



		/*if (n.qp_itemName == "_") {
			return nullptr;
		}*/
		//UGameplayEffect* GE;
		//if (qp_itemEffects.Contains(n.qp_itemName)) {
		//	GE = qp_itemEffects[n.qp_itemName];
		//	/*FGameplayModifierInfo& Mod = GE->Modifiers.AddDefaulted_GetRef();
		//	Mod.Attribute = FGameplayAttribute(AttrProp);
		//	Mod.ModifierOp = EGameplayModOp::AddBase;
		//	Mod.ModifierMagnitude = FScalableFloat(Value);*/

		//	//return;
		//}
		//else {
		//	GE = NewObject<UGameplayEffect>(nullptr);
		//	GE->AddToRoot();
		//	qp_itemEffects.Add(n.qp_itemName, GE);
		//}

		//int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp() ;

		UQPDA_Item* itemD = QP_GetItemData(n.qp_itemName);

		if (UQPDA_ItemTransform* itemA = Cast<UQPDA_ItemTransform>(itemD)) {

			//APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

			//AQPCharacter* m = Cast<AQPCharacter>(PC->GetPawn());
			if (m->qp_assetData->qp_name == itemA->qp_transformName)
			{
				return;
			}
			//----------------------------------

			

			//// 2. Spawn 新角色（禁用碰撞修正）
			//FActorSpawnParameters Params;
			//Params.SpawnCollisionHandlingOverride =
			//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//FTransform(m->GetActorRotation(), FeetLocation)

			//

			//// 4. 用新 Capsule 半高还原 Z
			//

			//// 5. Possess
			//

			//// 6. 再启用移动
			//NewChar->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

			//----------------------------------

			float OldHalf = m->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			FVector FeetLocation = m->GetActorLocation() - FVector(0, 0, OldHalf);

			AQPCharacter* nA =(AQPCharacter*) UQPGIM_Character::qp_staticObject->QP_GetNewCharacter(itemA->qp_transformName, FTransform(m->GetActorRotation(), FeetLocation), true);


			float NewHalf = nA->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			nA->SetActorLocation(FeetLocation + FVector(0, 0, NewHalf+200));
			//UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_AddFTransform("Transform", FTransform(m->GetActorRotation(), FeetLocation+ FVector(0, 0, NewHalf + 200)));
			UQPGIM_Character::qp_staticObject->QP_Possess(m->GetController(), itemA->qp_transformName, true, false, true);
			nA->SetActorLocation(FeetLocation + FVector(0, 0, NewHalf));

			nA->QP_PlayTrasformNs();
			UQPGIM_Character::qp_staticObject->QP_CollectCharacter(m->qp_assetData->qp_name, m);
			nA->qp_materialAutoRestore->QP_SetMatAmount(0.6);
			
			nA->GetController()->SetControlRotation(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFRotator("ControllerRotation"));
			;

			return;
		}
		//GE->DurationPolicy = itemD->qp_GEType;

		float timeR = n.QP_GetDataScale();
		int timeT = n.QP_GetFreshType();
		/*(1 - (TimestampMs - n.qp_createTime) / n.qp_datas["qp_shelfLife"]);
		if (timeR >= 0.7) {

		}
		else if (timeR >= 0.3) {
			timeR = 0.7 - (0.7 - timeR) * 0.5;
		}
		else if (timeR > 0) {

			timeR = 0.5 - (0.3 - timeR);

		}*/

		if (timeT == 3) {
			//timeR = 0.2 * (1 + timeR);


			n.qp_datas["qp_poison"] = (n.qp_datas["qp_poison"] - n.qp_datas["qp_rottenPoison"] * n.QP_GetDataScaleEX()) / timeR * 2;
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
			if (!n.qp_datas.Contains(AttrProp->GetFName())) {
				continue;
			}
			//FProperty* DataProp = itemD->GetClass()->FindPropertyByName(AttrProp->GetFName());
			//if (!DataProp) continue;
			//if(n.qp_datas.Contains())

			//if( n.qp)
			//float Value = 0.f;
			//DataProp->CopyCompleteValue(&Value, DataProp->ContainerPtrToValuePtr<void>(itemD));
			m->qp_abilitySystemComponent->ApplyModToAttribute(
				FGameplayAttribute(AttrProp),
				EGameplayModOp::AddBase,
				n.qp_datas[AttrProp->GetFName()] * timeR
			);
			/*FGameplayModifierInfo& Mod = GE->Modifiers.AddDefaulted_GetRef();
			Mod.Attribute = FGameplayAttribute(AttrProp);
			Mod.ModifierOp = EGameplayModOp::AddBase;
			Mod.ModifierMagnitude = FScalableFloat(n.qp_datas[AttrProp->GetFName()] * timeR);*/
		}
		FGameplayCueParameters Params;
		Params.Location = m->GetActorLocation();
		//FGameplayTag tag = QPTags::QPCue::UseFood;
			m->qp_abilitySystemComponent->ExecuteGameplayCue(QPTags::QPCue::UseFood, Params);
		//m->qp_abilitySystemComponent->ExecuteGameplayCue()
		//m->qp_abilitySystemComponent->ExecuteGameplayCue(FGameplayTag::RequestGameplayTag("QPTags.QPAbilites.UseFood"), Params);


		//t[index].qp_itemName = "_";
	}
}