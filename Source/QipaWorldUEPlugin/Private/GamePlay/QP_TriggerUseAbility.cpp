// QIPAWORLD


#include "GamePlay/QP_TriggerUseAbility.h"





void AQP_TriggerUseAbility::QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!______))))))))"));
	//qp_autoEmissive = 1;
	//qp_isShow = true;
	AQPMonster* m = (AQPMonster*)OtherActor;
	//qp_abilities

		if (!HasAuthority() || !m->qp_abilitySystemComponent) return;

		for (auto AbilityClass : qp_abilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpecHandle Handle =
				m->qp_abilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
			m->qp_abilitySystemComponent->TryActivateAbility(Handle);
		qp_abilityHandles.Add(Handle);
	}
		//UE_LOG(LogTemp, Warning, TEXT("___!_sdfsd____ddddddddddddddddddddddddd_))))))))"));

}

void AQP_TriggerUseAbility::QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AQPMonster* m = (AQPMonster*)OtherActor;


 	if (!HasAuthority() || !m->qp_abilitySystemComponent) return;

	for (const FGameplayAbilitySpecHandle& Handle : qp_abilityHandles)
	{
		m->qp_abilitySystemComponent->ClearAbility(Handle);
	}

	qp_abilityHandles.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("___!_sdfsd_____))))))))"));
	//qp_isShow = false;
	//qp_autoEmissive = -1;


	/*for (auto v : qp_materials)
	{

		v->SetScalarParameterValue("qp_emissive", 0);
	}*/

}