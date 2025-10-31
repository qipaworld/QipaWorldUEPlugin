// QIPAWORLD


#include "AttributeSet/QPAS_Health.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

void UQPAS_Health::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UQPAS_Health, qp_health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQPAS_Health, qp_maxHealth, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UQPAS_Health::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	/*if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}*/
}

void UQPAS_Health::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	/*if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}*/
}

void UQPAS_Health::OnRep_qp_health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQPAS_Health, qp_health, OldHealth);
}

void UQPAS_Health::OnRep_qp_maxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQPAS_Health, qp_maxHealth, OldMaxHealth);
}