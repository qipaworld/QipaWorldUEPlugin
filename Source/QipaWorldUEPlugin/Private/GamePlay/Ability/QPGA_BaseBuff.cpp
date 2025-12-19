// QIPAWORLD


#include "GamePlay/Ability/QPGA_BaseBuff.h"


#include "GameplayEffect.h"


//void UQPGA_BaseBuff::ActivateAbility(
//    const FGameplayAbilitySpecHandle Handle,
//    const FGameplayAbilityActorInfo* ActorInfo,
//    const FGameplayAbilityActivationInfo ActivationInfo,
//    const FGameplayEventData* TriggerEventData)
//{
//    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
// 
// FGameplayEffectSpecHandle HealEffect = MakeOutgoingGameplayEffectSpec(HealEffectClass, 1);
//ActiveHealEffectHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, HealEffect);

//    //ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, qp_effect, 1, 1.f);
//    //EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
//}

//void UQPGA_BaseBuff::EndAbility(
//    const FGameplayAbilitySpecHandle Handle,
//    const FGameplayAbilityActorInfo* ActorInfo,
//    const FGameplayAbilityActivationInfo ActivationInfo,
//    bool bReplicateEndAbility,
//    bool bWasCancelled)
//{
//    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
//
//    // 停止计时器、清除任务、移除效果等
//    UE_LOG(LogTemp, Warning, TEXT("HealAbility Ended (Cancelled=%d)"), bWasCancelled);
//
//    // 举例：移除一个持续Effect
//    if (ActiveHealEffectHandle.IsValid())
//    {
//        ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveHealEffectHandle);
//    }
// if (ActiveHealEffectHandle.IsValid())
//{
//    GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveHealEffectHandle);
//    }
//}

	// void UQPGA_BaseBuff::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
	// {
	// Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	// }
