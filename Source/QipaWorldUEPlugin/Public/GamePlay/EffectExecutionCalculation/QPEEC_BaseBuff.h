// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "QPEEC_BaseBuff.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPEEC_BaseBuff : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
    UQPEEC_BaseBuff();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& Params,
		FGameplayEffectCustomExecutionOutput& Out) const override;
	
	
};
