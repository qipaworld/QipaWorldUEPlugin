// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QPGIM_Localization.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Localization : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UQPGIM_Localization* QP_UQPGIM_Localization;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

public:
	///**包含全部支持的语言*/
	//UPROPERTY(BlueprintReadWrite)
	//TMap<FString, FString> qp_LocalizationList;

	/**设置地区*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	bool QP_SetCurrentCulture(const FString& InCultureName);

	/**获得地区*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	FString QP_GetCurrentLocale();

	/**获得地区显示名称*/

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	FString QP_GetCultureDisplayName(const FString& Culture,const bool Localized);
	
	/**获得支持地区的列表*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	TArray< FString > QP_GetLocalizedCultures() const;

	/**在支持地区的列表里选择一个合适的语言*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Sound")
	FString QP_GetSuitableCulture(TArray< FString > AvailableCultures, FString CulturetoMatch, FString FallbackCulture);
		
};
