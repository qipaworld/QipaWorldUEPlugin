// Fill out your copyright notice in the Description page of Project Settings.


#include "Localization/QPGIM_Localization.h"
//#include "Internationalization/PolyglotTextData.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include <Kismet/KismetInternationalizationLibrary.h>
#include "Kismet/KismetSystemLibrary.h"

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"
UQPGIM_Localization* UQPGIM_Localization::qp_staticObject = nullptr;


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
	qp_localizationData = UQPGIM_Data::qp_staticObject->QP_GetUQPData("UQPGIM_Localization");
	//QP_GameLocalizationDataChange()
	FInternationalization::Get().OnCultureChanged().AddUObject(this, &UQPGIM_Localization::QP_GameLocalizationDataChange);
	QP_InitStaticObject();

	//LoadYaml("");
	//qp_gameQPdataBase = NewObject<UQPData>();
}
void UQPGIM_Localization::QP_InitStaticObject() {
	UQPGIM_Localization::qp_staticObject = this;
}
void UQPGIM_Localization::QP_GameLocalizationDataChange() {
	qp_localizationData->QP_AddFString("Language", QP_GetCurrentLanguage());

	//const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("QP_DelayBroad"), this);
	//UKismetSystemLibrary::Delay(this, 0.1f, LatentInfo);

}
void UQPGIM_Localization::QP_DelayBroad() {

	//qp_localizationData->QP_AddFString("QP_DelayLanguageChange", QP_GetCurrentLanguage());
}

void UQPGIM_Localization::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;
}

FString UQPGIM_Localization::QP_GetL10NAssetsPath(FString path) {
	//path.Replace
	FString qp_IETF = QP_GetCurrentLanguage();
	std::string cstr(TCHAR_TO_UTF8(*path));
	int l10nindex = cstr.find("/QPL10N/");

	if (l10nindex != -1) {
		if (path.Contains(qp_IETF, ESearchCase::CaseSensitive)) {
			return path;
		}
		else {
			int l10nindex_l = l10nindex + 8;
			int l10nindex_2 = cstr.find("/", l10nindex_l);
			cstr.replace(l10nindex_l, l10nindex_2- l10nindex_l, TCHAR_TO_UTF8( *qp_IETF));
			return FString(cstr.c_str());
		}
	}
	//int index = cstr.find("/Game/");
	//if (index == -1) {
		int indextype = cstr.find("'/");
		if (indextype == -1) {
			int indexEnd = cstr.find("/",1);
			cstr.replace(indexEnd, 1, TCHAR_TO_UTF8(*FString::Printf(TEXT("/QPL10N/%s/"), *qp_IETF)));
			return FString(cstr.c_str());
		}
		else {
			int indexEnd = cstr.find("/", indextype+2);
			cstr.replace(indexEnd, 1, TCHAR_TO_UTF8(*FString::Printf(TEXT("/QPL10N/%s/"), *qp_IETF)));
			return FString(cstr.c_str());
		}
	//}
	
	//cstr.replace(index, 6, TCHAR_TO_UTF8(*FString::Printf(TEXT("/Game/QPL10N/%s/"), *qp_IETF)));
	//return FString(cstr.c_str());
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
	//qp_localizationData->QP_AddFString("QP_LanguageChange", InCultureName,true);
	//GLog->Log("jumpStdssssssssssssssssdddddddddddrt");

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