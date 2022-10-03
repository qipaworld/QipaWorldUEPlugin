// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/QPGIM_UserInterface.h"
//#include <Subsystems/PanelExtensionSubsystem.h>
//#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Setting/QPDeveloperSettings.h"
#include "Data/QPGIM_Data.h"

#include "Data/QPData.h"
UQPGIM_UserInterface* UQPGIM_UserInterface::QP_UQPGIM_UserInterface = nullptr;


bool UQPGIM_UserInterface::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_UserInterface::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());
	UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData("mapData")->qp_dataDelegate.AddUObject(this, &UQPGIM_UserInterface::QP_BindMapData);

	QP_UQPGIM_UserInterface = this;
	qp_mainUIPath = UQPDeveloperSettings::QP_GET()->QP_DefaultMainUserInterfacePath;
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
	if (key == "None")
		key = path;

	ConstructorHelpers::FClassFinder<UUserWidget> widgetClass(*path);
	return QP_AddUserInterfaceByClass(widgetClass.Class, key);
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterface(UUserWidget* widget, FString key)
{
	
	if (qp_UIData.Contains(key)) {
		key += FString::FromInt(qp_UIData.Num());
	}

	qp_UIData.Add(key, widget);
	qp_topWidgetkey = key;
	widget->AddToViewport(qp_UIData.Num());
	return widget;
}

UUserWidget* UQPGIM_UserInterface::QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget> widgetClass, FString key)
{
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

	return QP_AddUserInterface(widget,key);
}

void UQPGIM_UserInterface::QP_RemoveUserInterface(FString key)
{
	UUserWidget* widget = nullptr;

	if (key == "None") {
		widget = qp_UIData[qp_topWidgetkey];
	}
	else if(qp_UIData.Contains(key)) {
		widget = qp_UIData[key];
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("没有UI---%S"),*key);
	}
	if (widget != nullptr) {
		widget->RemoveFromParent();
	}

}

void UQPGIM_UserInterface::QP_ResetUIData()
{
	qp_UIData.Reset();
}

void UQPGIM_UserInterface::QP_BindMapData(const UQPData* data)
{
	if (data->qp_changeMap.Contains("baseLevelName")) {
		QP_ResetUIData();
	}
	
}
