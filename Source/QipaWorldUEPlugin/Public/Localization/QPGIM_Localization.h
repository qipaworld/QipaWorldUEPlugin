// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Localization.generated.h"

class UQPData;

/**
 * 本地化管理类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Localization : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Localization* QP_UQPGIM_Localization;
	//国际化资源路径
	//FString qp_localizationAssetsPath = ;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	/**数据管理器里的数据名字*/
	FString qp_localizationDataName = "qp_sLocalizationDataName";

	/**国际化数据*/
	UPROPERTY(BlueprintReadWrite, Category = "QipaWorld|QPLocalization")
		UQPData* qp_localizationData;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	///**包含全部支持的语言*/
	//UPROPERTY(BlueprintReadWrite)
	//TMap<FString, FString> qp_LocalizationList;

	/**获得国际化资源路径*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
		FString QP_GetL10NAssetsPath(FString path);

	/**设置语言*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
		bool QP_SetCurrentLanguage(FString InCultureName);

	/**获得语言*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
		FString QP_GetCurrentLanguage();

	/**设置地区*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
		bool QP_SetCurrentLocale(FString InCultureName);

	///**获得地区*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	//	const FString QP_GetCurrentLocale(const FString& InCultureName);


	/**设置所有，比如地区和语言和资产*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	bool QP_SetCurrentCulture(FString InCultureName);

	/**设置所有，比如地区和语言和资产*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	bool QP_SetCurrentLanguageAndLocale(FString InCultureName, const bool SaveToConfig);

	/**获得地区*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	FString QP_GetCurrentLocale();

	/**获得地区显示名称*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	FString QP_GetCultureDisplayName(FString Culture,bool Localized);
	
	/**获得支持地区的列表*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	TArray< FString > QP_GetLocalizedCultures() const;

	/**在支持地区的列表里选择一个合适的语言*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
	FString QP_GetSuitableCulture(TArray< FString > AvailableCultures, FString CulturetoMatch, FString FallbackCulture);
	
	/**在支持地区的列表里选择一个合适的语言*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPLocalization")
		void QP_SetSuitableCulture();

	void QP_GameLocalizationDataChange();

};
