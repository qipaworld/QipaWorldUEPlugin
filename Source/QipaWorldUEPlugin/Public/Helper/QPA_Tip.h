// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Helper/QPA_HelperBase.h"
#include "QPA_Tip.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Tip : public AQPA_HelperBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
		/** ºÏ≤‚Ã· æid*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Helper")
	bool QP_HelperTip();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "QipaWorld|Helper")
	void QP_HelperTipCell();
};
