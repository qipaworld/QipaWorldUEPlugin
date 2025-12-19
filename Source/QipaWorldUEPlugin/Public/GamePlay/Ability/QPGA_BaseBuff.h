// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "QPGA_BaseBuff.generated.h"

/**
 *
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPGA_BaseBuff : public UGameplayAbility
{
	GENERATED_BODY()
	
	//UPROPERTY(EditDefaultsOnly, Category = "Ability")
	//UGameplayEffect* qp_effect;

	
	/*virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;*/

	/*void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled);*/

	//virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);

	
};
