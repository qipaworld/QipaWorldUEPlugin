// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/QPObject.h"
#include "Data/QPData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Components/ListView.h"
#include "Components/VerticalBox.h"
#include "Widget/QP_ShowInformationCell.h"

#include "QPGIM_UserInterface.generated.h"

class UQPData;
/**
 * 用户界面管理类
 */

//UENUM(BlueprintType)
//enum class EBindViewDataType : uint8
//{
//	qpInt32               UMETA(DisplayName = "Int32"),
//	qpFString               UMETA(DisplayName = "FString"),
//};

UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_UserInterface : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_UserInterface* qp_staticObject;
	virtual void QP_InitStaticObject();

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
	//FString qp_mainUIPath;

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_SetAutoMouse(bool b);
	/**添加主UI*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	//UUserWidget* QP_AddMainUserInterface();

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	//UUserWidget* QP_AddMainPopUserInterface(UUserWidget* widget, const FString& key = "MainUserInterface");

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	//UUserWidget* QP_AddMainPopUserInterfaceByClass(TSubclassOf<UUserWidget>  widgetClass, const FString& key = "MainUserInterface");

	/**check user interface is open?*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	bool QP_CheckUserInterface(const FString& key);

	/**get user interface is open?*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_GetUserInterface(const FString& key);

	/**用路径添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterfaceByPath(const FString& path,const FString& key = "None");

	/**用实例添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterface(UUserWidget* widget, const FString& key = "None");

	/**用class添加UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UUserWidget* QP_AddUserInterfaceByClass(TSubclassOf<UUserWidget>  widgetClass, const FString& key = "None", bool only = false);
	/**删除UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_RemoveUserInterface(const FString& key = "None");

	/**删除所有UI*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_RemoveAllUserInterface();
	/*清空ui数据，但是不会删除ui*/
	void QP_ResetUIData();
	/**获得player0 然后监听默认的ui键盘事件*/
	void QP_BindKeyBoard(UQPData* data);

	void QP_BindMapData(UQPData* data);
	/**控制鼠标显示与隐藏*/
	//void QP_UpdateMouse(bool b);
	/**监听默认ui事件，没有ui就弹出主菜单，有了就弹出最上面的
	* 这里绑定的player0，没有player0可能就不能用了，所以在蓝图里监听一下也可以
	* 但是在项目设置的qipaworld插件中关闭ui事件。
	*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	//void QP_AutoPopOrPush(UUserWidget* widget);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")

	void QP_AutoPopOrPushByClass(TSubclassOf<UUserWidget>  widgetClass);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")

	void QP_AutoPopOrPushByClassEx(TSubclassOf<UUserWidget>  widgetClass, const FString& key);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")

	void QP_AutoPopOrPush(UUserWidget* widget);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")

	void QP_AutoPopOrPushEx(UUserWidget* widget, const FString& key);

	UFUNCTION(BlueprintPure, Category = "QipaWorld|QPUserInterface")
	int32 QP_GetPopUINum();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_ListViewBindData(FName key,  UListView* view, TSubclassOf<UQPObject> itemClass,UQPData* data, EQPDataKeyType t,EQPDataValueType vt,bool isUpdateChange = false);

	template<typename K, typename V>
	void QP_ListViewBindData_CPP(FName key,  UListView* view, TSubclassOf<UQPObject> itemClass, UQPData* data, EQPDataKeyType t, EQPDataValueType vt, bool isUpdateChange = false) {
		
		TSharedPtr < TMap<K, UQPObject*>> items = MakeShared< TMap<K, UQPObject*>>();
		
		
		UQPObject* obj = nullptr;
		TArray<K> keys;
		//data->QP_CheckQPBaseData<K, V>(vt, t);
		((IQPBaseData*)data->QP_GetBaseData<K,V>(vt,t))->QP_GetMapKeys(keys);
		for (auto v : keys) {
			obj = NewObject<UQPObject>(view, itemClass);

			if constexpr (std::is_same<K, FName>::value)
			{
				obj->QP_SetObjTag(v);
			}
			else
			{
				obj->QP_SetObjId(v);
			}
			items->Add(v, obj);
			view->AddItem(obj);
		}

		//UQPUtil::QP_LOG_EX<int>("_____________", itemsExI->Num());
		qp_viewDataHandele.Add(key, data->qp_dataDelegate.AddLambda([view, itemClass, t,vt, items, data, key, this, isUpdateChange](UQPData* lambData) {
			if (!IsValid(view)) {
				UQPUtil::QP_LOG("listView auto Update  view  is null " + itemClass->ClassConfigName.ToString());
				QP_ListViewUnbindData(key, view, data);
				return;
			}
			UQPObject* obj = nullptr;

			for (auto v : (lambData->QP_GetChangeMap<K,V>(vt,t))) {
				if (v.Value == EQPDataChangeType::REMOVE) {
					view->RemoveItem((*items)[v.Key]);
					items->Remove(v.Key);
				}
				else if (v.Value == EQPDataChangeType::ADD) {
					obj = NewObject<UQPObject>(view, itemClass);
					
					if constexpr (std::is_same<K, FName>::value)
					{
						obj->QP_SetObjTag(v.Key);
					}
					else
					{
						obj->QP_SetObjId(v.Key);
					}
					
					items->Add(v.Key, obj);
					
					view->AddItem(obj);
				}
				else if (v.Value == EQPDataChangeType::CLEAR) {
					items->Reset();
					view->ClearListItems();
				}
				else if (v.Value == EQPDataChangeType::CHANGE) {
					if (isUpdateChange) {
						view->RemoveItem((*items)[v.Key]);
						view->AddItem((*items)[v.Key]);
						//items->Remove(v.Key);
					}
				}
			}
			}));

	}
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_ListViewUnbindData( FName key, class UListView* view, UQPData* data);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	UQPData* QP_GetEventData(FName key);

	TMap<FName, FDelegateHandle> qp_viewDataHandele;


	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPUserInterface")
	void QP_InitShowInformation(UPanelWidget* root,TSubclassOf<UQP_ShowInformationCell>  widgetClass,UQPData* d, int startIndex = 0,int cellMax = 13);

};
