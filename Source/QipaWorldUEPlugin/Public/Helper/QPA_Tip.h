// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Helper/QPA_HelperBase.h"
#include "QPA_Tip.generated.h"

/**
 * 教程提示类，可以理解为一次性弹框
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Tip : public AQPA_HelperBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
		/** 检测提示id*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPTip")
	bool QP_HelperTip();
	//弹出提示后做什么，这个在蓝图里根据实际情况写方法。
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "QipaWorld|QPTip")
	void QP_HelperTipCell();
};
