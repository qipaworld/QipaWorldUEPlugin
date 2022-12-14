// Fill out your copyright notice in the Description page of Project Settings.


#include "Localization/QPGIM_Localization.h"
//#include "Internationalization/PolyglotTextData.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include <Kismet/KismetInternationalizationLibrary.h>

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
UQPGIM_Localization* UQPGIM_Localization::QP_UQPGIM_Localization = nullptr;


bool UQPGIM_Localization::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Localization::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());
	//FInternationalization::Get().OnCultureChanged().add
	qp_localizationData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData(qp_localizationDataName);
	//QP_GameLocalizationDataChange()
	FInternationalization::Get().OnCultureChanged().AddUObject(this, &UQPGIM_Localization::QP_GameLocalizationDataChange);
	QP_UQPGIM_Localization = this;

	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}
void UQPGIM_Localization::QP_GameLocalizationDataChange() {
	qp_localizationData->QP_AddFString("Language", QP_GetCurrentLanguage());
}
void UQPGIM_Localization::Deinitialize()
{
	Super::Deinitialize();
}
FString UQPGIM_Localization::QP_GetL10NAssetsPath(FString path) {
	//path.Replace
	std::string cstr(TCHAR_TO_UTF8(*path));
	
	int index = cstr.find("/Game/");
	cstr.replace(index, 6, TCHAR_TO_UTF8(*FString::Printf(TEXT("/Game/QPL10N/%s/"), *QP_GetCurrentLanguage())));
	return FString(cstr.c_str());
	// , *QP_GetCurrentLanguage(), *path);
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
bool UQPGIM_Localization::QP_SetCurrentLanguageAndLocale(FString InCultureName, const bool SaveToConfig) {
	return UKismetInternationalizationLibrary::SetCurrentLanguageAndLocale(InCultureName, SaveToConfig);

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

void UQPGIM_Localization::QP_SetSuitableCulture() {
	
	QP_SetCurrentLanguageAndLocale(QP_GetSuitableCulture(QP_GetLocalizedCultures(), FGenericPlatformMisc::GetDefaultLanguage(), "en"),true);
	
}