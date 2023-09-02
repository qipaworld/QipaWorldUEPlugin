// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Helper/QPGIM_Helper.h"
#include "QPGIM_Tip.generated.h"

/**
 * 弹框管理类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGIM_Tip : public UQPGIM_Helper
{
	GENERATED_BODY()

public:
	static UQPGIM_Tip* qp_staticObject;

	/*UFUNCTION(BlueprintCallable,Category = "QipaWorld|Data")
	void QP_Init();*/

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

protected:
	virtual void QP_LoadHelperData() override;


};
