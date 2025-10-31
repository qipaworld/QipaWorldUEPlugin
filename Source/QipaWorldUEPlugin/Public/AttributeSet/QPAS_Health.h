// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "QPAS_Health.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPAS_Health : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Monster")
	//float qp_health = 100;
	
    // Ѫ��
    UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData qp_health;
    //ATTRIBUTE_ACCESSORS(UQPAS_Health, qp_health)
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UQPAS_Health, qp_health)
            GAMEPLAYATTRIBUTE_VALUE_GETTER(qp_health)
            GAMEPLAYATTRIBUTE_VALUE_SETTER(qp_health)
            GAMEPLAYATTRIBUTE_VALUE_INITTER(qp_health)

        // ���Ѫ��
        UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData qp_maxHealth;
    //ATTRIBUTE_ACCESSORS(UQPAS_Health, qp_maxHealth)
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UQPAS_Health, qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_GETTER(qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_SETTER(qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_INITTER(qp_maxHealth)

        // ������
       /* UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackPower)*/

    // ����������Щ������Ҫ�������н��и���
            virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
        // ��Attribute��CurrentValue���ı�֮ǰ����
        virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
        // ����instant Gameplay EffectʹAttribute��BaseValue�ı�ʱ����
        virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

        UFUNCTION()
        void OnRep_qp_health(const FGameplayAttributeData& OldHealth);
        UFUNCTION()
        void OnRep_qp_maxHealth(const FGameplayAttributeData& OldMaxHealth);
        
	
};
