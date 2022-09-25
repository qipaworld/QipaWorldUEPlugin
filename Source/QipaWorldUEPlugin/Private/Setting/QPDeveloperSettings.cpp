// Fill out your copyright notice in the Description page of Project Settings.


#include "Setting/QPDeveloperSettings.h"

//UQPDeveloperSettings::DefaultBackgroundAudioPath = "None";
/** Gets the settings container name for the settings, either Project or Editor */
//FName UQPDeveloperSettings::GetContainerName() const
//{ return TEXT("QipaWorldPlugin1"); }
/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
FName UQPDeveloperSettings::GetCategoryName() const
{ return TEXT("QipaWorldPlugin"); }
///** The unique name for your section of settings, uses the class's FName. */
//FName UQPDeveloperSettings::GetSectionName() const
//{ return TEXT("QipaWorldPlugin3"); }

/** Gets the section text, uses the classes DisplayName by default. */
FText UQPDeveloperSettings::GetSectionText() const 
{ return FText::FromString(TEXT("Plugin Default Setting")); }
/** Gets the description for the section, uses the classes ToolTip by default. */
FText UQPDeveloperSettings::GetSectionDescription() const 
{ return FText::FromString(TEXT("Plugin Default Setting")); }


UQPDeveloperSettings* UQPDeveloperSettings::QP_GET() 
{
	return GetMutableDefault<UQPDeveloperSettings>(); 
}

UQPDeveloperSettings::UQPDeveloperSettings()
{
	//DefaultBackgroundAudioPath = "None";
	//DefaultUIClickAudioPath = "None";
}
