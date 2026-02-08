// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/QPGIM_UserInterface.h"
//#include <Subsystems/PanelExtensionSubsystem.h>
//#include "WidgetBlueprint.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/UserWidget.h"
#include "Map/QPGIM_Map.h"
#include "GamePlay/AttributeSet/QPAS_BaseBuff.h"
#include "Internationalization/Text.h"
#include "Monster/QPMonster.h"
#include "Internationalization/StringTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Setting/QPDS_Default.h"
#include "Data/QPGIM_Data.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPData.h"
#include "Character/QPDA_Character.h"
#include "Data/QPGIM_BaseData.h"
#include "DataAsset/QPDataAsset.h"
#include "Item/QPGIM_Item.h"
#include "Item/QPDA_ItemTransform.h"

#include "Item/QPA_Item.h"
#include "QPUtil.h"
UQPGIM_UserInterface* UQPGIM_UserInterface::qp_staticObject = nullptr;


bool UQPGIM_UserInterface::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_UserInterface::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Map::StaticClass());
	UQPGIM_Map::qp_staticObject->QP_GetMapData()->qp_dataDelegate.AddUObject(this, &UQPGIM_UserInterface::QP_BindMapData);
	UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->qp_dataDelegate.AddUObject(this, &UQPGIM_UserInterface::QP_BindKeyBoard);
	QP_InitStaticObject();
	//UQPDS_Default* devSetting = UQPDS_Default::QP_GET();
	
	//qp_mainUIPath = UQPGIM_BaseData::qp_defaultDataAsset->QP_DefaultMainUserInterfacePath;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
	
	
}
void UQPGIM_UserInterface::QP_InitStaticObject() {
	UQPGIM_UserInterface::qp_staticObject = this;
}
void UQPGIM_UserInterface::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;
}
//UUserWidget* UQPGIM_UserInterface::QP_AddMainPopUserInterface(UUserWidget* widget, const FString& key) {
//	/*TSubclassOf<UUserWidget> w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainPopUserInterface.Get();
//	if (!IsValid(w)) {
//		w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainPopUserInterface.LoadSynchronous();
//	}
//	if (IsValid(w)) {*/
//		return QP_AddUserInterfaceByClass(w, key);
//	//}
//	
//	UQPUtil::QP_LOG("MainUI not open");
//
//	return nullptr;
//	
//}
//UUserWidget* QP_AddMainPopUserInterfaceByClass(TSubclassOf<UUserWidget>  widgetClass, const FString& key) {
//	/*TSubclassOf<UUserWidget> w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainPopUserInterface.Get();
//	if (!IsValid(w)) {
//		w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainPopUserInterface.LoadSynchronous();
//	}
//	if (IsValid(w)) {*/
//	return QP_AddUserInterfaceByClass(w, key);
//	//}
//
//	UQPUtil::QP_LOG("MainUI not open");
//
//	return nullptr;
//
//}
//UUserWidget* UQPGIM_UserInterface::QP_AddMainUserInterface()
//{
//	//return QP_AddUserInterfaceByClass(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.Get(),key);
//	TSubclassOf<UUserWidget> w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.Get();
//	if (!IsValid(w)) {
//		w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.LoadSynchronous();
//	}
//	if (IsValid(w)) {
//		
//		UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), w);
//		widget->AddToViewport();
//		return widget;
//	}
//	
//	UQPUtil::QP_LOG("MainUI not open");
//
//	return nullptr;
//	
//
//	
//}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterfaceByPath(const FString& path, const FString& key)
{
	TSubclassOf<UUserWidget> widgetClass = LoadClass< UUserWidget>(nullptr, *path);
	if (key == "None") {
		//key = path;
		return QP_AddUserInterfaceByClass(widgetClass, path);
	}
	else {
		return QP_AddUserInterfaceByClass(widgetClass, key);

	}
	//ConstructorHelpers::FClassFinder<UUserWidget> widgetClass(*path);
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterface(UUserWidget* widget, const FString& key)
{
	
	if (qp_UIData.Contains(key)) {
		qp_UIDataKey.Add(key+ FString::FromInt(qp_UIData.Num()));
	}
	else {
		qp_UIDataKey.Add(key);
	}
		qp_UIData.Add(qp_UIDataKey.Last(), widget);
	//qp_topWidgetkey = key;
	widget->AddToViewport(qp_UIData.Num());
	if (qp_autoMouse) {
		UQPUtil::QP_UpdateMouse(true);
	}
	
	return widget;
}

/**check user interface is open?*/
bool UQPGIM_UserInterface::QP_CheckUserInterface(const FString& key) {
	return qp_UIData.Contains(key);
}

/**get user interface is open?*/
UUserWidget* UQPGIM_UserInterface::QP_GetUserInterface(const FString& key) {
	if (qp_UIData.Contains(key)) {

		return qp_UIData[key];
	}
	return nullptr;
}


UUserWidget* UQPGIM_UserInterface::QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget> widgetClass, const FString& key, bool only)
{
	if (only&& QP_CheckUserInterface(key)) {
		UQPUtil::QP_LOG("UI is only and UI is open "+key);

		return nullptr;
	}
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

	return QP_AddUserInterface(widget,key);
}

void UQPGIM_UserInterface::QP_RemoveUserInterface(const FString& key, bool autoMouse)
{
	FString realKey = key;
	if (key == "None") {
		realKey = qp_UIDataKey.Last();
	}
	 
	if(qp_UIData.Contains(realKey)) {
		
		qp_UIDataKey.Remove(realKey);
		qp_UIData.FindAndRemoveChecked(realKey)->RemoveFromParent();
		if (qp_UIData.Num() < 1) {
			if (autoMouse&&qp_autoMouse) {
				UQPUtil::QP_UpdateMouse( false);
			}
			//QP_UpdateMouse(false);
		}
	}
	else {
		UQPUtil::QP_LOG("not have UI "+key);
	}

}


void UQPGIM_UserInterface::QP_RemoveAllUserInterface()
{
	for (FString realKey: qp_UIDataKey)
	{
		if (qp_UIData.Contains(realKey)) {
			qp_UIData[realKey]->RemoveFromParent();
		}
	}
	if (qp_autoMouse) {
		UQPUtil::QP_UpdateMouse(false);
	}
	qp_UIDataKey.Reset();
	qp_UIData.Reset();

}

void UQPGIM_UserInterface::QP_SetAutoMouse(bool b) {
	qp_lastAutoMouse = qp_autoMouse;
	qp_autoMouse = b;
}
void UQPGIM_UserInterface::QP_AutoPopOrPushByClass(TSubclassOf<UUserWidget>  widgetClass)
{
	if (qp_UIData.Num() < 1) {
		if (IsValid(widgetClass)) {
			QP_AddUserInterfaceByClass(widgetClass);
		}
	}
	else {
		QP_RemoveUserInterface();
	}
}
void UQPGIM_UserInterface::QP_AutoPopOrPushByClassEx(TSubclassOf<UUserWidget>  widgetClass, const FString& key) {
	if (QP_CheckUserInterface(key)) {
		QP_RemoveUserInterface(key);
	}else if (IsValid(widgetClass)) {
		QP_AddUserInterfaceByClass(widgetClass,key);
	}
}

void UQPGIM_UserInterface::QP_AutoPopOrPush(UUserWidget* widget)
{
	if (qp_UIData.Num() < 1) {
		if (IsValid(widget)) {
			QP_AddUserInterface(widget);
		}
	}
	else {
		QP_RemoveUserInterface();
	}
}
void UQPGIM_UserInterface::QP_AutoPopOrPushEx(UUserWidget* widget, const FString& key) {
	if (QP_CheckUserInterface(key)) {
		QP_RemoveUserInterface(key);
	}
	else if (IsValid(widget)) {
		QP_AddUserInterface(widget, key);
	}
}

int32 UQPGIM_UserInterface::QP_GetPopUINum() {
	return qp_UIData.Num();
}
void UQPGIM_UserInterface::QP_BindKeyBoard(UQPData* data)
{
	/*if (data->QP_IsChange<FName, bool>("autoPushAndPopUI", EQPDataValueType::BOOL)) {
		QP_KeyBoardEvent();
	}
	else*/
		/*if (data->QP_IsChange<FName, bool>("AddMainUI", EQPDataValueType::BOOL)) {
		QP_AddMainUserInterface();
	}*/
}
void UQPGIM_UserInterface::QP_ResetUIData()
{

	qp_UIData.Reset();
	qp_UIDataKey.Reset();
	if (qp_autoMouse) {
		UQPUtil::QP_UpdateMouse( false);
	}
	//QP_UpdateMouse(false);
	
}

void UQPGIM_UserInterface::QP_BindMapData(UQPData* data)
{
	
		if (data->QP_IsChange<FName, FName>("changeLevelName", EQPDataValueType::FNAME)) {
			QP_ResetUIData();
		}
		
	
}
void UQPGIM_UserInterface::QP_ListViewBindData(FName key, UListView* view,  TSubclassOf<UQPObject> itemClass, UQPData* data, EQPDataKeyType t, EQPDataValueType vt, bool isUpdateChange) {

	if (qp_viewDataHandele.Contains(key)) {
		UQPUtil::QP_LOG("QP_ListViewBindData Error   Contains View " + LexToString( key));
		return;
	}

	if ( t == EQPDataKeyType::INT32 ) {
		if (vt == EQPDataValueType::INT32) {
			QP_ListViewBindData_CPP<int32, int32>(key, view, itemClass, data, t, vt, isUpdateChange);
		}
		else {
			QP_ListViewBindData_CPP<int32, FName>(key, view, itemClass, data, t, vt, isUpdateChange);
		}
	}
	else {
		if (vt == EQPDataValueType::INT32) {
			QP_ListViewBindData_CPP<FName, int32>(key, view, itemClass, data, t, vt, isUpdateChange);
		}
		else {
			QP_ListViewBindData_CPP<FName, FName>(key, view, itemClass, data, t, vt, isUpdateChange);
		}
	}
	
	
}
void UQPGIM_UserInterface::QP_ListViewUnbindData( FName key, class UListView* view, UQPData* data) {
	if (qp_viewDataHandele.Contains(key)) {
		data->qp_dataDelegate.Remove(qp_viewDataHandele[key]);
		qp_viewDataHandele.Remove(key);
	}
	else {
		UQPUtil::QP_LOG("QP_ListViewRemoveData Error qp_viewDataHandele not have view " + key.ToString());
	}
}
UQPData* UQPGIM_UserInterface::QP_GetEventData(FName key) {

	return UQPGIM_BaseData::qp_staticObject->QP_GetUIEventData()->QP_GetUQPData(key);
}

void UQPGIM_UserInterface::QP_InitShowInformation(UPanelWidget* root, TSubclassOf<UQP_ShowInformationCell>  widgetClass, int startIndex, int cellMax, bool isEx) {
	//UPanelWidget* dddd;
	UQPData* inData = UQPGIM_BaseData::qp_staticObject->QP_GetShowInformationData();
	TMap<FName, UQP_ShowInformationCell*> cells;
	UQP_ShowInformationCell* widget;
	//bool is_self = inData->QP_Getbool("qp_showIsSelf");
	//if (is_self) {
		//APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		//ACharacter* Character = PC ? : nullptr;
		AQPMonster* m = Cast<AQPMonster>(inData->QP_GetUObject("dataAsset"));
		if (!m) {
			return;
		}
		bool isBind = m->GetController()->IsLocalPlayerController();
		inData->QP_AddFName("showActorName", m->qp_assetData->qp_name);
		if (const UAttributeSet* uset = m->qp_abilitySystemComponent->GetAttributeSet(UQPAS_BaseBuff::StaticClass())) {
			
			FString sKey; 
			int32 exKey = 0; 
			
			if (isEx) {
				sKey = inData->QP_GetFString("qp_showExKey");
				exKey = inData->QP_Getint32("qp_showExKeyI");
				inData->QP_AddFText("qp_showMeshName", FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", sKey));
				sKey = sKey.Mid(2);
			}
			else {
				inData->QP_AddFText("qp_showMeshName", FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", m->qp_assetData->qp_name.ToString()));
			}
			//inData->QP_AddFVector("qp_showMeshVector", m->qp_assetData->qp_vector);
			//inData->QP_AddUObject("qp_showMesh", m->GetMesh()->GetSkeletalMeshAsset());
			//inData->QP_Addbool("isStatic", true);
			//inData->QP_GetUQPData("ControlData")->QP_Addbool("changeMesh", true);
			UClass* usetClass = uset->GetClass();
			UObject* DefaultObj = usetClass->GetDefaultObject();

			FProperty* Property;
			int DefaultValue = 0;
			float nowValue = 0;
			FStructProperty* StructProp;
			FName n;
			
			
			for (TFieldIterator<FProperty> It(usetClass); It; ++It)
			{
				Property = *It;
				StructProp = CastField<FStructProperty>(Property);
				if (StructProp)
				{
					if (StructProp->Struct == TBaseStructure<FGameplayAttributeData>::Get())
					{
						DefaultValue = (static_cast<FGameplayAttributeData*>(StructProp->ContainerPtrToValuePtr<void>(DefaultObj)))->GetBaseValue();

						nowValue = (static_cast<const FGameplayAttributeData*>(StructProp->ContainerPtrToValuePtr<void>(uset)))->GetBaseValue();
						n = Property->GetFName();
						if (isEx) {
							if (DefaultValue & exKey) {
								if (n.ToString().Contains(sKey)) {
									widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
									widget->qp_showMonster = m;
									widget->qp_data = inData;
									widget->qp_now = nowValue;
									//widget->qp_isShowSelf = is_self;
									widget->qp_nameText = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", n.ToString());

									cells.Add(n, widget);
								}
								
							}
						}
						else if (DefaultValue & (uint16)EQPBaseBuffDataType::ShowInformation) {

							widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
							widget->qp_showMonster = m;

							widget->qp_data = inData;
							//widget->qp_isShowSelf = is_self;
							widget->qp_dataName = n;
							widget->qp_max = nowValue;
							widget->qp_now = nowValue;
							widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(n);
							//UQPUtil::QP_LOG(FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", TEXT("qp_health")).ToString() + "_____1");
							//FSoftObjectPath TablePath(TEXT("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation"));
							//UStringTable* StringTable = Cast<UStringTable>(TablePath.TryLoad());

							//check(StringTable);
							//IStringTableEngineBridge::FullyLoadStringTableAsset(FName("DST_QP_ShowInformation"));


							//FText::FromStringTable(n, n);
							widget->qp_nameText = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", n.ToString());
							//UQPUtil::QP_LOG(n.ToString());
							//UQPUtil::QP_LOG(widget->qp_nameText.ToString());

							widget->qp_isBind = false;
							cells.Add(n, widget);
						}
						else if (DefaultValue & (uint16)EQPBaseBuffDataType::ShowInformationNow) {
							if (cells.Contains(n)) {
								widget = cells[n];
							}
							else {
								widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
								widget->qp_showMonster = m;

								widget->qp_data = inData;
								//widget->qp_isShowSelf = is_self;
								cells.Add(n, widget);
							}
							widget->qp_dataName = n;
							widget->qp_isBind = isBind;
							widget->qp_now = nowValue;
							widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(n);
							widget->qp_nameText = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", n.ToString());
							//UQPUtil::QP_LOG(n.ToString());
							//UQPUtil::QP_LOG(widget->qp_nameText.ToString());


						}
						else if (DefaultValue & (uint16)EQPBaseBuffDataType::ShowInformationMax) {
							/*FString Str =;

							Str.LeftChop(3);*/

							
							 FName newN = FName(*(n.ToString().LeftChop(3)));
							if (cells.Contains(newN)) {
								widget = cells[newN];
							}
							else {
								widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
								widget->qp_showMonster = m;

								//widget->qp_dataName = n;
								widget->qp_data = inData;
								//widget->qp_isShowSelf = is_self;
								cells.Add(newN, widget);
							}
							widget->qp_max = nowValue;
							//widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(n);
							//widget->qp_nameText = FText::FromStringTable("DST_QP_ShowInformation", n.ToString());
						}
						else if (DefaultValue & (uint16)EQPBaseBuffDataType::ShowInformationMin) {
							/*FString Str =;

							Str.LeftChop(3);*/


							FName newN = FName(*(n.ToString().LeftChop(3)));
							if (cells.Contains(newN)) {
								widget = cells[newN];
							}
							else {
								widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
								widget->qp_showMonster = m;

								//widget->qp_dataName = n;
								widget->qp_data = inData;
								//widget->qp_isShowSelf = is_self;
								cells.Add(newN, widget);
							}
							widget->qp_min = nowValue;
							//widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(n);
							//widget->qp_nameText = FText::FromStringTable("DST_QP_ShowInformation", n.ToString());
						}

					}

				}


				//UE_LOG(LogTemp, Log, TEXT("____%s"), *Property->GetFName().ToString());
			}
			//baseBuffData_Add->QP_SaveDataFAES("baseBuffDataSet_Add" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_Add_A" + qp_assetData->qp_name.ToString())));
			//baseBuffData->QP_SaveDataFAES("baseBuffDataSet" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_A" + qp_assetData->qp_name.ToString())));
		}
	//}
	//else if (UQPDataAsset* DA = Cast<UQPDataAsset>(inData->QP_GetUObject("dataAsset"))) {
		//inData->QP_Addbool("isStatic", false);
		
		//for (TFieldIterator<FProperty> It(DA->GetClass()); It; ++It)
		//{
		//	FProperty* Property = *It;

		//	//FString Name = Property->GetName();
		//	//;
		//	//UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
		//	//if(Property->GetFName().ToString() == "qp_health")
		//	if (Property->HasMetaData(TEXT("QP_LocalData"))) {
		//		//qp_abilitySystemComponent->SetNumericAttributeBase(FGameplayAttribute(Property), baseBuffData->QP_Getfloat(Property->GetFName()));
		//	}
		//	else if (Property->HasMetaData(TEXT("QP_LocalDataBase"))) {
		//		//FGameplayAttribute p(Property);
		//		//float num = qp_abilitySystemComponent->GetNumericAttributeBase(p);
		//		//qp_abilitySystemComponent->SetNumericAttributeBase(p, num + baseBuffData_Add->QP_Getfloat(Property->GetFName()));
		//	}

		//	//UE_LOG(LogTemp, Log, TEXT("____%s"), *Property->GetFName().ToString());
		//}
	//}

	
	
	UVerticalBox* VB = nullptr;
	UWidget* w = nullptr;
	int i = 0;
	int j = 0;
	int z = 0;
	for (auto v2 : cells) {

		if (!VB) {
			
			while (true)
			{
				w = root->GetChildAt(z);
				if (!w) {
					break;
				}
				z++;
				VB = Cast<UVerticalBox>(w);
				if (VB )
				{
					++i;
					if (i > startIndex) {
						break;
					}
					// 这是一个 VerticalBox
				}
			}
			if (!VB) {
				break;
			}
		}
		VB->AddChildToVerticalBox(v2.Value);
		j++;
		if ( j >= cellMax) {
			VB = nullptr;
			j = 0;
		}
		
	}
	
}


void UQPGIM_UserInterface::QP_InitShowInformationPlayerItem(UPanelWidget* root, TSubclassOf<UQP_ShowInformationCell>  widgetClass, int startIndex, int cellMax, bool isEx) {
	//UPanelWidget* dddd;
	UQPData* inData = UQPGIM_BaseData::qp_staticObject->QP_GetShowInformationData();
	TMap<FName, UQP_ShowInformationCell*> cells;
	UQP_ShowInformationCell* widget;
	int index = inData->QP_Getint32("qp_showItemIndex");
	if (index>=0) {
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		FQPItem& item = UQPGIM_Item::qp_staticObject->QP_GetPlayerItem(index);
		
		inData->QP_AddFName("showActorName", item.qp_itemName);
		//UQPUtil::QP_LOG(item.qp_itemName.ToString());
		FText showName = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", item.qp_itemName.ToString());
		inData->QP_AddFText("qp_showMeshName", showName);

			int timeT = item.QP_GetFreshType();
			float timeR = item.QP_GetDataScale();
			/*bool isFor = true;
			if (item.qp_datas.Contains("qp_itemTypeF")) {
				isFor = item.qp_datas["qp_itemTypeF"] != 1;
			}*/
			if (!Cast<UQPDA_ItemTransform>(UQPGIM_Item::qp_staticObject->QP_GetItemData(item.qp_itemName))) {
				for (auto v : item.qp_datas) {
					if (v.Key == "qp_range" ||
						v.Key == "qp_outWaterProportion" ||
						v.Key == "qp_outVitaminProportion" ||
						v.Key == "qp_outMineralProportion" ||
						v.Key == "qp_outSugarProportion" ||
						v.Key == "qp_outProteinProportion" ||
						v.Key == "qp_outFatProportion" ||
						v.Key == "qp_itemTypeF" ||
						v.Key == "qp_outPoisonProportion") {
						continue;
					}
					widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
					widget->qp_data = inData;
					widget->qp_dataName = v.Key;
					widget->qp_now = timeR * v.Value;
					widget->qp_min = 0;
					widget->qp_max = v.Value;
					//widget->qp_isShowSelf = false;
					//widget->qp_isBind = isBind;
					widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(v.Key);
					widget->qp_nameText = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", v.Key.ToString());
					cells.Add(v.Key, widget);


				}
			}
					if (cells.Contains("qp_shelfLife")) 
					{

						cells["qp_shelfLife"]->qp_now = (item.qp_datas["qp_shelfLife"] * item.QP_GetDataScaleEX()) * timeR;
				//}
						
						FText t = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", FString::Printf(TEXT("fresh_%d"), timeT));

							
						inData->QP_AddFText("qp_showMeshName", FText::Format(FText::FromString(TEXT("{0} {1} {2}")), showName, FText::FromString(TEXT(" - ")), t));

						/*switch (timeT)
						{
						case 0: {
							break;
						}
						case 1: {
							break;
						}
						case 2: {
							break;
						}
						case 3: {
							break;
						}
						default:
							break;
						}
						if (timeT == 0) {

						}else if*/
						if (timeT == 3) 
						{
							cells["qp_poison"]->qp_now = (item.qp_datas["qp_poison"] - item.qp_datas["qp_rottenPoison"] * item.QP_GetDataScaleEX())*2;
							cells["qp_poison"]->qp_max = item.qp_datas["qp_rottenPoison"] + item.qp_datas["qp_poison"];
						}
					}
			

	}
	else if (AQPA_Item* DA = Cast<AQPA_Item>(inData->QP_GetUObject("dataAsset"))) {
		FQPItem& item = DA->qp_itemData;
		inData->QP_AddFName("showActorName", item.qp_itemName);
		UQPUtil::QP_LOG(item.qp_itemName.ToString());
		inData->QP_AddFText("qp_showMeshName", FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", item.qp_itemName.ToString()));

		int timeT = item.QP_GetFreshType();
		float timeR = item.QP_GetDataScale();

		if (!Cast<UQPDA_ItemTransform>(UQPGIM_Item::qp_staticObject->QP_GetItemData(item.qp_itemName))) {
			for (auto v : item.qp_datas) {
				if (v.Key == "qp_range" ||
					v.Key == "qp_outWaterProportion" ||
					v.Key == "qp_outVitaminProportion" ||
					v.Key == "qp_outMineralProportion" ||
					v.Key == "qp_outSugarProportion" ||
					v.Key == "qp_outProteinProportion" ||
					v.Key == "qp_outFatProportion" ||
					v.Key == "qp_itemTypeF" ||
					v.Key == "qp_outPoisonProportion") {
					continue;
				}
				widget = CreateWidget<UQP_ShowInformationCell>(GetWorld(), widgetClass);
				widget->qp_data = inData;
				widget->qp_dataName = v.Key;
				widget->qp_now = timeR * v.Value;
				widget->qp_min = 0;
				widget->qp_max = v.Value;
				//widget->qp_isShowSelf = false;
				//widget->qp_isBind = true;
				widget->qp_texture = UQPGIM_BaseData::qp_staticObject->QP_GetTexture(v.Key);
				widget->qp_nameText = FText::FromStringTable("/Game/QipaWorld3D/LocalizationKey/DST_QP_ShowInformation.DST_QP_ShowInformation", v.Key.ToString());
				cells.Add(v.Key, widget);


			}
		}
		if (cells.Contains("qp_shelfLife")) {

			cells["qp_shelfLife"]->qp_now = (item.qp_datas["qp_shelfLife"] * item.QP_GetDataScaleEX()) * timeR;
			//}
			if (timeT == 3) {
				cells["qp_poison"]->qp_now = (item.qp_datas["qp_poison"] - item.qp_datas["qp_rottenPoison"] * item.QP_GetDataScaleEX()) * timeR;

			}
		}
	}



	UVerticalBox* VB = nullptr;
	UWidget* w = nullptr;
	int i = 0;
	int j = 0;
	int z = 0;
	for (auto v2 : cells) {

		if (!VB) {

			while (true)
			{
				w = root->GetChildAt(z);
				if (!w) {
					break;
				}
				z++;
				VB = Cast<UVerticalBox>(w);
				if (VB)
				{
					++i;
					if (i > startIndex) {
						break;
					}
					// 这是一个 VerticalBox
				}
			}
			if (!VB) {
				break;
			}
		}
		VB->AddChildToVerticalBox(v2.Value);
		j++;
		if (j >= cellMax) {
			VB = nullptr;
			j = 0;
		}

	}

}
void UQPGIM_UserInterface::QP_AutoPosition(UUserWidget* Widget, UPanelWidget* c, float offset) {



	FGeometry Geo = c->GetCachedGeometry();

	//FVector2D AbsoluteSize = Geo.GetAbsoluteSize();

	//FVector2D AbsolutePosition = Geo.GetAbsolutePosition();
	//UQPUtil::QP_LOG(AbsoluteSize.ToString() + "_____________________AbsoluteSize");
	//UQPUtil::QP_LOG(AbsoluteSize.ToString() + "_____________________AbsoluteSize");

	if (!Widget || !c)
	{
		return;
	}

	/*APlayerController* PC = Widget->GetOwningPlayer();
	if (!PC)
	{
		PC = GEngine->GetFirstLocalPlayerController(Widget->GetWorld());
		if (!PC) return;
	}*/
	
	
	FVector2D WidgetSize = c->GetDesiredSize();

	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(Widget);
	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(Widget);

	ViewportSize = ViewportSize / ViewportScale;
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(Widget);
	//UQPUtil::QP_LOG(MousePosition.ToString() + "_____________________AbsoluteSize");
	//UQPUtil::QP_LOG_EX("____________", ViewportScale);

	FVector2D MousePos;
	MousePos.Y = MousePosition.Y - WidgetSize.Y - offset;
	MousePos.X = MousePosition.X - WidgetSize.X/2;
	
	if (MousePos.Y < 0)
	{
		MousePos.Y = MousePosition.Y  + offset;
	}
	float xEx = MousePos.X + WidgetSize.X;
	if (xEx > ViewportSize.X)
	{
		
		MousePos.X = MousePos.X - (xEx - ViewportSize.X) - offset;
	}else if (MousePos.X < 0)
	{
		MousePos.X = offset;
	}
	

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(c->Slot);
	if (!CanvasSlot)
	{
		return;
	}

	CanvasSlot->SetPosition(MousePos);

	
}