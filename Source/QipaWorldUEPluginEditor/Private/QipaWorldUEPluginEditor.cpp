// Copyright Epic Games, Inc. All Rights Reserved.

#include "QipaWorldUEPluginEditor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Templates/SharedPointer.h"
#include "AssetTypeAction/QPAssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FQipaWorldUEPluginEditorModule"

void FQipaWorldUEPluginEditorModule::StartupModule()
{
	//这里是加载自定义资源的地方
	// 由于更改这插件初始化位置，所以这里失效了
	// 这个等用到在研究
	// 应该可以等到引擎初始化完毕后在加载这个
	// 
	//--------------加载资源开始
	// 
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FQPAssetTypeActions));
	//--------------加载资源结束
	
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

void FQipaWorldUEPluginEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQipaWorldUEPluginEditorModule, QipaWorldUEPluginEditor)