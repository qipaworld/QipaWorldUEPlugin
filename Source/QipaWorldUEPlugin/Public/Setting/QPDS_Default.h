// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "QPDS_Default.generated.h"

/**
 * 
 */
UCLASS(Config = QipaWorldPluginSetting, defaultconfig, meta = (DisplayName = "Plugin Default Setting"))
class QIPAWORLDUEPLUGIN_API UQPDS_Default : public UDeveloperSettings
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
	UFUNCTION(BlueprintPure,DisplayName = "UQPDS_Default")
	static UQPDS_Default* QP_GET();

public:
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultBackgroundAudioPath = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultUIClickAudioPath = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	bool QP_BackgroundAudioAutoPlay = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultStartMap = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultLoadingMap = "None";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultMainUserInterfacePath = "None";

	/*这个是默认的看出ui动作的key，你可以在动作管理器里加入这个事件，并且绑定按键。他会自动弹出和关闭ui*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FString QP_DefaultUserInterfaceActionKey = "DefaultUserInterfaceAction";
	/*如果这个为真，上面的key生效*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	bool QP_UserInterfaceAutoPop = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FString, int32> QP_UUID;

	UQPDS_Default();
};
