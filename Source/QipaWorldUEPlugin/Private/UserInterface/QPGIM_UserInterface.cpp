// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/QPGIM_UserInterface.h"
//#include <Subsystems/PanelExtensionSubsystem.h>
//#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "Map/QPGIM_Map.h"


#include "UObject/ConstructorHelpers.h"
#include "Setting/QPDS_Default.h"
#include "Data/QPGIM_Data.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPData.h"
#include "Data/QPGIM_BaseData.h"
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

	qp_staticObject = this;
	//UQPDS_Default* devSetting = UQPDS_Default::QP_GET();
	
	//qp_mainUIPath = UQPGIM_BaseData::qp_defaultDataAsset->QP_DefaultMainUserInterfacePath;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
	
	
}

void UQPGIM_UserInterface::Deinitialize()
{
	Super::Deinitialize();
}

UUserWidget* UQPGIM_UserInterface::QP_AddMainUserInterface(const FString& key)
{
	//return QP_AddUserInterfaceByClass(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.Get(),key);
	TSubclassOf<UUserWidget> w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.Get();
	if (!IsValid(w)) {
		w = UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultMainUserInterface.LoadSynchronous();

	}
	if (IsValid(w)) {
		return QP_AddUserInterfaceByClass(w, key);
	}
	else {
		UQPUtil::QP_LOG("MainUI not open");

		return nullptr;
	}

	
}

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

void UQPGIM_UserInterface::QP_RemoveUserInterface(const FString& key)
{
	FString realKey = key;
	if (key == "None") {
		realKey = qp_UIDataKey.Last();
	}
	 
	if(qp_UIData.Contains(realKey)) {
		
		qp_UIDataKey.Remove(realKey);
		qp_UIData.FindAndRemoveChecked(realKey)->RemoveFromParent();
		if (qp_UIData.Num() < 1) {
			if (qp_autoMouse) {
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
		QP_RemoveUserInterface(realKey);
	}

}

void UQPGIM_UserInterface::QP_SetAutoMouse(bool b) {
	qp_autoMouse = b;
}
void UQPGIM_UserInterface::QP_KeyBoardEvent()
{
	if (qp_UIData.Num() < 1) {
		QP_AddMainUserInterface();
	}
	else {
		QP_RemoveUserInterface();
	}
}
void UQPGIM_UserInterface::QP_BindKeyBoard()
{
	 
	if (UQPGIM_BaseData::qp_staticObject-> qp_defaultDataAsset->QP_UserInterfaceAutoPop) {

		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->InputComponent->BindAction(*(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey), IE_Released, this, &UQPGIM_UserInterface::QP_KeyBoardEvent);

	}
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
		else if (data->QP_IsChange<FName, FName>("baseLevelName", EQPDataValueType::FNAME)) {
			QP_BindKeyBoard();
		}
	//}
	
}
void UQPGIM_UserInterface::QP_ListViewBindData(FName key, UListView* view,  TSubclassOf<UQPObject> itemClass, UQPData* data, EQPDataKeyType t, EQPDataValueType vt) {

	if (qp_viewDataHandele.Contains(key)) {
		UQPUtil::QP_LOG("QP_ListViewBindData Error   Contains View " + LexToString( key));
		return;
	}

	if ( t == EQPDataKeyType::INT32 ) {
		if (vt == EQPDataValueType::INT32) {
			QP_ListViewBindData_CPP<int32, int32>(key, view, itemClass, data, t, vt);
		}
		else {
			QP_ListViewBindData_CPP<int32, FName>(key, view, itemClass, data, t, vt);
		}
	}
	else {
		if (vt == EQPDataValueType::INT32) {
			QP_ListViewBindData_CPP<FName, int32>(key, view, itemClass, data, t, vt);
		}
		else {
			QP_ListViewBindData_CPP<FName, FName>(key, view, itemClass, data, t, vt);
		}
	}
	
	
}
void UQPGIM_UserInterface::QP_ListViewRemoveData( FName key, class UListView* view, UQPData* data) {
	if (qp_viewDataHandele.Contains(key)) {
		data->qp_dataDelegate.Remove(qp_viewDataHandele[key]);
	}
	else {
		UQPUtil::QP_LOG("QP_ListViewRemoveData Error qp_viewDataHandele not have view " + key.ToString());
	}
}
UQPData* UQPGIM_UserInterface::QP_GetEventData(FName key) {

	return UQPGIM_BaseData::qp_staticObject->QP_GetUIEventData()->QP_GetUQPData(key);
}