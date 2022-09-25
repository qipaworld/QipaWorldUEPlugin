// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "QPDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = QipaWorldPluginSetting, defaultconfig, meta = (DisplayName = "Plugin Default Setting"))
class QIPAWORLDUEPLUGIN_API UQPDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	//virtual FName GetContainerName() const override;
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override;
	///** The unique name for your section of settings, uses the class's FName. */
	//virtual FName GetSectionName() const override;

	/** Gets the section text, uses the classes DisplayName by default. */
	virtual FText GetSectionText() const ;
	/** Gets the description for the section, uses the classes ToolTip by default. */
	virtual FText GetSectionDescription() const;

public:
	UFUNCTION(BlueprintPure,DisplayName = "QPDeveloperSettings")
	static UQPDeveloperSettings* QP_GET();

public:
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite, Category = "QipaWorld")
	FString DefaultBackgroundAudioPath = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString DefaultUIClickAudioPath = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString DefaultChangeMapLoadingPath = "None";

	UQPDeveloperSettings();
};
