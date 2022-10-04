// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/QPGIM_UserInterface.h"
//#include <Subsystems/PanelExtensionSubsystem.h>
//#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Setting/QPDeveloperSettings.h"
#include "Data/QPGIM_Data.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
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
	UQPDeveloperSettings* devSetting = UQPDeveloperSettings::QP_GET();
	qp_mainUIPath = devSetting->QP_DefaultMainUserInterfacePath;
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
		
		qp_UIDataKey.RemoveAt(qp_UIDataKey.Num()-1);
		qp_UIData.FindAndRemoveChecked(realKey)->RemoveFromParent();
		if (qp_UIData.Num() < 1) {
			QP_UpdateMouse(false);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("没有UI---%S"),*key);
	}

}

void UQPGIM_UserInterface::QP_UpdateMouse(bool b) {
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetShowMouseCursor(b);
	if (b) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUI(controller);
	}
	else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(controller);
	}

}
void UQPGIM_UserInterface::QP_BindKeyBoard()
{

	if (qp_UIData.Num() < 1) {
		QP_AddMainUserInterface();
	}
	else {
		QP_RemoveUserInterface();
	}
}
void UQPGIM_UserInterface::QP_ResetUIData()
{

	qp_UIData.Reset();
	QP_UpdateMouse(false);
	UQPDeveloperSettings* devSetting = UQPDeveloperSettings::QP_GET();
	if (devSetting->QP_UserInterfaceAutoPop) {

		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->InputComponent->BindAction(*(devSetting->QP_DefaultUserInterfaceActionKey), IE_Released, this, &UQPGIM_UserInterface::QP_BindKeyBoard);

	}
}

void UQPGIM_UserInterface::QP_BindMapData(const UQPData* data)
{
	if (data->qp_changeMap.Contains("baseLevelName")) {
		QP_ResetUIData();
	}
	
}
