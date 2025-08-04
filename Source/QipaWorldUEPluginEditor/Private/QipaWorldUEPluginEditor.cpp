// Copyright Epic Games, Inc. All Rights Reserved.

#include "QipaWorldUEPluginEditor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Templates/SharedPointer.h"
#include "LevelEditor.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "AssetTypeAction/QPAssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FQipaWorldUEPluginEditorModule"

void FQipaWorldUEPluginEditorModule::StartupModule()
{
	
	//UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQipaWorldUEPluginEditorModule::QP_RegisterMenus));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

	MenuExtender->AddMenuBarExtension(
		"Help", 
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FQipaWorldUEPluginEditorModule::QP_AddMenuBarMenu)
	);

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	//--------------
	// 
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FQPAssetTypeActions));
	//--------------
	
	//TSharedPtr<FQPAssetTypeActions> AssetTypeAction = MakeShareable(new FQPAssetTypeActions(AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("QPSoundClass")), LOCTEXT("QipaWorld", "QPSoundClass2")));
	//AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
	//Register
	//IAssetTools& AssetToolsModule =  FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//AssetCategory
	//; AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("UserDefinedAsset")), LOCTEXT("UserDefinedAssetCategory", "QipaWorld")
	//TSharedPtr<FQPAssetTypeActions> AssetTypeAction = MakeShareable(new FQPAssetTypeActions());
	//AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}
void FQipaWorldUEPluginEditorModule::QP_AddMenuBarMenu(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(
		LOCTEXT("QPTools_Label", "QPTools"),
		LOCTEXT("QPTools_Tooltip", "Open QPTools Menu"),
		FNewMenuDelegate::CreateRaw(this, &FQipaWorldUEPluginEditorModule::QP_GenerateMenuContent),
		"QPTools"
	);
}
void FQipaWorldUEPluginEditorModule::QP_GenerateMenuContent(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("QPTools_Open", "Open Tool Window"),
		LOCTEXT("QPTools_Open_Tooltip", "Opens the QP Tool window."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FQipaWorldUEPluginEditorModule::QP_OpenToolWindow))
	);
}

void FQipaWorldUEPluginEditorModule::QP_OpenToolWindow()
{
	if (GEditor)
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		if (!EditorUtilitySubsystem)
		{
			UE_LOG(LogTemp, Error, TEXT("EditorUtilitySubsystem is null"));
			return;
		}
		
		FString WidgetPath = "/Script/Blutility.EditorUtilityWidgetBlueprint'/QipaWorldUEPlugin/Editor/Blueprint/Widget/QP_BPW_Tools.QP_BPW_Tools'";
		UEditorUtilityWidgetBlueprint* WidgetBP = Cast<UEditorUtilityWidgetBlueprint>(
			StaticLoadObject(UEditorUtilityWidgetBlueprint::StaticClass(), nullptr, *WidgetPath));

		if (!WidgetBP)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load Editor Utility Widget: %s"), *WidgetPath);
			return;
		}

		EditorUtilitySubsystem->SpawnAndRegisterTab(WidgetBP);
	}
	/*UWidgetBlueprint* WidgetBlueprint = 
	
		ensureMsgf(WidgetBlueprint->GeneratedClass, TEXT("Null generated class for WidgetBlueprint [%s]"), *WidgetBlueprint->GetName());
		if (WidgetBlueprint->GeneratedClass && WidgetBlueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{
			if (UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(WidgetBlueprint))
			{
				EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
			}
		}*/
	
}

void FQipaWorldUEPluginEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

//void FQipaWorldUEPluginEditorModule::QP_RegisterMenus()
//{
//	FToolMenuOwnerScoped OwnerScoped(this);
//
//	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
//
//	//FToolMenuSection& Section = Menu->AddSection("QPToolsSection",LOCTEXT("QPTddools", "QPToddols"));
//	//Menu->Sections[]
//	/*Section.AddSubMenu(
//		"QPToolsSubMenu",
//		LOCTEXT("QPTools_Label", "QP Tools"),
//		LOCTEXT("QPTools_Tooltip", "Open QP Tools options"),
//		FNewToolMenuDelegate::CreateLambda([](FToolMenuSection& SubSection)
//			{
//				SubSection.AddMenuEntry(
//					"SubTool1",
//					LOCTEXT("SubTool1_Label", "Open Tool 1"),
//					LOCTEXT("SubTool1_Tooltip", "Open the first tool"),
//					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Edit"),
//					FUIAction(FExecuteAction::CreateLambda([]()
//						{
//							UE_LOG(LogTemp, Warning, TEXT("Tool 1 Clicked"));
//						}))
//				);
//			})
//	);*/
//	//Menu->OnKeyDown()
//	//Menu->AddPullDownMenu(
//	//	"QPTools", // ID
//	//	LOCTEXT("QPTools_Label", "QPTools"), // 菜单栏上显示的名字
//	//	LOCTEXT("QPTools_Tooltip", "Qipa Tools Dropdown"), // 鼠标提示
//	//	FNewToolMenuDelegate::CreateRaw(this, &FQipaWorldUEPluginEditorModule::GenerateQipaDropdownMenu)
//	//);
//	Menu->AddMenuEntry("MainMenu", FToolMenuEntry::InitMenuEntry("QPTools",
//		LOCTEXT("QPTools", "QPTooddls"),
//		LOCTEXT("QPToolsTip", "onclick open QPTools"),
//		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Tool"),
//		FUIAction(FExecuteAction::CreateLambda([]() {
//			UE_LOG(LogTemp, Warning, TEXT("Hello clicked!"));
//			}))));
//	//Section.AddMenuEntry(
//		
//	
//
//	FGlobalTabmanager::Get()->RegisterNomadTabSpawner("QPToolTab",
//		FOnSpawnTab::CreateRaw(this, &FQipaWorldUEPluginEditorModule::QP_OnSpawnPluginTab))
//		.SetDisplayName(LOCTEXT("OpenWidget", "OpenWidget"))
//		.SetMenuType(ETabSpawnerMenuType::Hidden);
//}
//void FQipaWorldUEPluginEditorModule::QP_OpenToolWindow()
//{
//	UE_LOG(LogTemp, Warning, TEXT("QP_OpenToolWindow was called!"));
//	FGlobalTabmanager::Get()->TryInvokeTab(FName("QPToolTab"));
//}
TSharedRef<SDockTab> FQipaWorldUEPluginEditorModule::QP_OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(STextBlock).Text(LOCTEXT("MyTool", "这是我的编辑器工具窗口"))
		];
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQipaWorldUEPluginEditorModule, QipaWorldUEPluginEditor)