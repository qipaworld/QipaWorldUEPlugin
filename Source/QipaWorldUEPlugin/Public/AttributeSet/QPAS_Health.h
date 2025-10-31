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
	
    // 血量
    UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData qp_health;
    //ATTRIBUTE_ACCESSORS(UQPAS_Health, qp_health)
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UQPAS_Health, qp_health)
            GAMEPLAYATTRIBUTE_VALUE_GETTER(qp_health)
            GAMEPLAYATTRIBUTE_VALUE_SETTER(qp_health)
            GAMEPLAYATTRIBUTE_VALUE_INITTER(qp_health)

        // 最大血量
        UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData qp_maxHealth;
    //ATTRIBUTE_ACCESSORS(UQPAS_Health, qp_maxHealth)
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UQPAS_Health, qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_GETTER(qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_SETTER(qp_maxHealth)
        GAMEPLAYATTRIBUTE_VALUE_INITTER(qp_maxHealth)

        // 攻击力
       /* UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackPower)*/

    // 用于声明哪些属性需要在网络中进行复制
            virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
        // 当Attribute的CurrentValue被改变之前调用
        virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
        // 仅在instant Gameplay Effect使Attribute的BaseValue改变时触发
        virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

        UFUNCTION()
        void OnRep_qp_health(const FGameplayAttributeData& OldHealth);
        UFUNCTION()
        void OnRep_qp_maxHealth(const FGameplayAttributeData& OldMaxHealth);
        
	
};
