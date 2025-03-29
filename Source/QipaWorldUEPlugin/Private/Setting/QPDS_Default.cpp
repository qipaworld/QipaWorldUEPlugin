// Fill out your copyright notice in the Description page of Project Settings.


#include "Setting/QPDS_Default.h"

//UQPDeveloperSettings::DefaultBackgroundAudioPath = "None";
/** Gets the settings container name for the settings, either Project or Editor */
//FName UQPDeveloperSettings::GetContainerName() const
//{ return TEXT("QipaWorldPlugin1"); }
/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
FName UQPDS_Default::GetCategoryName() const
{ return TEXT("QipaWorldPlugin"); }
///** The unique name for your section of settings, uses the class's FName. */
//FName UQPDeveloperSettings::GetSectionName() const
//{ return TEXT("QipaWorldPlugin3"); }

/** Gets the section text, uses the classes DisplayName by default. */
FText UQPDS_Default::GetSectionText() const
{ return FText::FromString(TEXT("Plugin Default Setting")); }
/** Gets the description for the section, uses the classes ToolTip by default. */
FText UQPDS_Default::GetSectionDescription() const
{ return FText::FromString(TEXT("Plugin Default Setting")); }


UQPDS_Default* UQPDS_Default::QP_GET()
{
	return GetMutableDefault<UQPDS_Default>();
}

UQPDS_Default::UQPDS_Default()
{
	QP_PackageKey = "qipaworld";
	QP_SetingDataAsset = TSoftObjectPtr<UQPDS_DataAsset>(FSoftObjectPath(TEXT("/Script/QipaWorldUEPlugin.QPDS_DataAsset'/Game/QipaWorld3D/DataAsset/QP_DefaultSetting.QP_DefaultSetting'")));

	//DefaultBackgroundAudioPath = "None";
	//DefaultUIClickAudioPath = "None";
}
