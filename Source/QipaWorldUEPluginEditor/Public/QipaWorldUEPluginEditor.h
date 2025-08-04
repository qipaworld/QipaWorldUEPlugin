// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FQipaWorldUEPluginEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//void QP_RegisterMenus();
	//static void QP_OpenToolWindow();
	TSharedRef<SDockTab> QP_OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
	void QP_AddMenuBarMenu(FMenuBarBuilder& MenuBarBuilder);
	void QP_GenerateMenuContent(FMenuBuilder& MenuBuilder);
	void QP_OpenToolWindow();

};
