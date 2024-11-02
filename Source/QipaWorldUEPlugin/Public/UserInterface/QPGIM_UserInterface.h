// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_UserInterface.generated.h"

//class UQPData；
/**
 * 用户界面管理类
 */


UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_UserInterface : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_UserInterface* qp_staticObject;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	bool qp_autoMouse = true;

public:
	/**所有的ui都存这里面*/
	TMap<FString, UUserWidget*> qp_UIData;
	/**为了能按顺序弹出，所以单独存了key*/
	TArray<FString> qp_UIDataKey;

	//FString qp_topWidgetkey;
	/**主ui路径*/
	FString qp_mainUIPath;

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_SetAutoMouse(bool b);
	/**添加主UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddMainUserInterface(FString key = "MainUserInterface");

	/**check user interface is open?*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	bool QP_CheckUserInterface(FString key);

	/**get user interface is open?*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_GetUserInterface(FString key);

	/**用路径添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterfaceByPath(FString path,FString key = "None");

	/**用实例添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterface(UUserWidget* widget, FString key = "None");

	/**用class添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget>  widgetClass, FString key = "None", bool only = false);
	/**删除UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_RemoveUserInterface(FString key = "None");

	/**删除所有UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_RemoveAllUserInterface();
	/*清空ui数据，但是不会删除ui*/
	void QP_ResetUIData();
	/**获得player0 然后监听默认的ui键盘事件*/
	void QP_BindKeyBoard();

	void QP_BindMapData(UQPData* data);
	/**控制鼠标显示与隐藏*/
	//void QP_UpdateMouse(bool b);
	/**监听默认ui事件，没有ui就弹出主菜单，有了就弹出最上面的
	* 这里绑定的player0，没有player0可能就不能用了，所以在蓝图里监听一下也可以
	* 但是在项目设置的qipaworld插件中关闭ui事件。
	*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_KeyBoardEvent();
};
