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
	
	qp_mainUIPath = UQPGIM_BaseData::qp_defaultDataAsset->QP_DefaultMainUserInterfacePath;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
	
	
}

void UQPGIM_UserInterface::Deinitialize()
{
	Super::Deinitialize();
}

UUserWidget* UQPGIM_UserInterface::QP_AddMainUserInterface(FString key)
{
	return QP_AddUserInterfaceByPath(qp_mainUIPath,key);
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterfaceByPath(FString path,FString key)
{
	if (key == "None") {
		key = path;
	}
	TSubclassOf<UUserWidget> widgetClass = LoadClass< UUserWidget>(nullptr, *path);
	//ConstructorHelpers::FClassFinder<UUserWidget> widgetClass(*path);
	return QP_AddUserInterfaceByClass(widgetClass, key);
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterface(UUserWidget* widget, FString key)
{
	
	if (qp_UIData.Contains(key)) {
		key += FString::FromInt(qp_UIData.Num());
	}

	qp_UIData.Add(key, widget);
	//qp_topWidgetkey = key;
	qp_UIDataKey.Add(key);
	widget->AddToViewport(qp_UIData.Num());
	
	QP_UpdateMouse(true);
	return widget;
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget> widgetClass, FString key)
{
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

	return QP_AddUserInterface(widget,key);
}

void UQPGIM_UserInterface::QP_RemoveUserInterface(FString key)
{
	FString realKey = key;
	if (key == "None") {
		realKey = qp_UIDataKey.Last();
	}
	 
	if(qp_UIData.Contains(realKey)) {
		
		qp_UIDataKey.Remove(realKey);
		qp_UIData.FindAndRemoveChecked(realKey)->RemoveFromParent();
		if (qp_UIData.Num() < 1) {
			QP_UpdateMouse(false);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not have UI---%s"),*key);
	}

}


void UQPGIM_UserInterface::QP_RemoveAllUserInterface()
{
	for (FString realKey: qp_UIDataKey)
	{
		QP_RemoveUserInterface(realKey);
	}

}
void UQPGIM_UserInterface::QP_UpdateMouse(bool b) {
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetShowMouseCursor(b);
	if (b) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(controller);
	}
	else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(controller);
	}

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
	 
	if (UQPGIM_BaseData::qp_defaultDataAsset->QP_UserInterfaceAutoPop) {

		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->InputComponent->BindAction(*(UQPGIM_BaseData::qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey), IE_Released, this, &UQPGIM_UserInterface::QP_KeyBoardEvent);

	}
}
void UQPGIM_UserInterface::QP_ResetUIData()
{

	qp_UIData.Reset();
	qp_UIDataKey.Reset();
	QP_UpdateMouse(false);
	
}

void UQPGIM_UserInterface::QP_BindMapData(UQPData* data)
{
	if (data->qp_changeMap.Contains("changeLevelName")) {
		QP_ResetUIData();
	}
	else if (data->qp_changeMap.Contains("baseLevelName")) {
		QP_BindKeyBoard();
	}
}
