// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_UserInterface.generated.h"

//class UQPData；
/**
 * 
 */


UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_UserInterface : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_UserInterface* QP_UQPGIM_UserInterface;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	TMap<FString, UUserWidget*> qp_UIData;
	TArray<FString> qp_UIDataKey;

	//FString qp_topWidgetkey;

	FString qp_mainUIPath;

	/**添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|UserInterface")
	UUserWidget* QP_AddMainUserInterface(FString key = "MainUserInterface");


	/**用路径添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|UserInterface")
	UUserWidget* QP_AddUserInterfaceByPath(FString path,FString key = "None");

	/**添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|UserInterface")
	UUserWidget* QP_AddUserInterface(UUserWidget* widget, FString key = "None");

	/**添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|UserInterface")
	UUserWidget* QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget>  widgetClass, FString key = "None");

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|UserInterface")
	void QP_RemoveUserInterface(FString key = "None");
	/*情况ui数据，但是不会删除ui*/
	void QP_ResetUIData();


	void QP_BindMapData(const UQPData* data);

	void QP_UpdateMouse(bool b);

	void QP_BindKeyBoard();
};
