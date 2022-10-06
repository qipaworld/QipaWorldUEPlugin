// Fill out your copyright notice in the Description page of Project Settings.


#include "Localization/QPGIM_Localization.h"
//#include "Internationalization/PolyglotTextData.h"
#include <Kismet/KismetInternationalizationLibrary.h>

UQPGIM_Localization* UQPGIM_Localization::QP_UQPGIM_Localization = nullptr;


bool UQPGIM_Localization::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Localization::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGameInstanceDataManager::StaticClass());

	QP_UQPGIM_Localization = this;
	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}

void UQPGIM_Localization::Deinitialize()
{
	Super::Deinitialize();
}

bool UQPGIM_Localization::QP_SetCurrentLanguage(FString InCultureName)
{
	return UKismetInternationalizationLibrary::SetCurrentLanguage(InCultureName);
}

FString UQPGIM_Localization::QP_GetCurrentLanguage()
{
	return UKismetInternationalizationLibrary::GetCurrentLanguage();
}

bool UQPGIM_Localization::QP_SetCurrentLocale(FString InCultureName)
{
	return UKismetInternationalizationLibrary::SetCurrentLocale(InCultureName);
}



bool UQPGIM_Localization::QP_SetCurrentCulture(FString InCultureName)
{
	return UKismetInternationalizationLibrary::SetCurrentCulture(InCultureName);
}

FString UQPGIM_Localization::QP_GetCurrentLocale()
{
	return UKismetInternationalizationLibrary::GetCurrentLocale();
}

FString UQPGIM_Localization::QP_GetCultureDisplayName(FString Culture, bool Localized)
{
	return UKismetInternationalizationLibrary::GetCultureDisplayName(Culture, Localized);
}

TArray<FString> UQPGIM_Localization::QP_GetLocalizedCultures() const
{
	return UKismetInternationalizationLibrary::GetLocalizedCultures(true);
}

FString UQPGIM_Localization::QP_GetSuitableCulture(TArray<FString> AvailableCultures, FString CulturetoMatch, FString FallbackCulture)
{
	return UKismetInternationalizationLibrary::GetSuitableCulture(AvailableCultures, CulturetoMatch, FallbackCulture);
}
