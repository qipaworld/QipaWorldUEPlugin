// QIPAWORLD


#include "GamePlay/EffectExecutionCalculation/QPEEC_BaseBuff.h"

#include "GamePlay/AttributeSet/QPAS_BaseBuff.h"




UQPEEC_BaseBuff::UQPEEC_BaseBuff()
{
    //RelevantAttributesToCapture.Add(UQPAS_BaseBuff::GetAttackAttribute());
    //RelevantAttributesToCapture.Add(UQPAS_BaseBuff::GetDefenseAttribute());
    //RelevantAttributesToCapture.Add(UQPAS_BaseBuff::GetCritChanceAttribute());
}

 void UQPEEC_BaseBuff::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& Params,
    FGameplayEffectCustomExecutionOutput& Out) const 
{

    // float qp_health, qp_vitamin, qp_oxygen, qp_water, qp_mineral;
     /*Params.AttemptCalculateCapturedAttributeMagnitude(
         UQPAS_BaseBuff::GetAttackAttribute(), qp_health);
     Params.AttemptCalculateCapturedAttributeMagnitude(
         UQPAS_BaseBuff::GetDefenseAttribute(), qp_vitamin);
     Params.AttemptCalculateCapturedAttributeMagnitude(
         UQPAS_BaseBuff::GetCritChanceAttribute(), qp_oxygen);
     Params.AttemptCalculateCapturedAttributeMagnitude(
         UQPAS_BaseBuff::GetCritChanceAttribute(), qp_water);*/

    /* if (qp_health <= 0 || qp_vitamin <= 0 || qp_oxygen <= 0 || qp_water <= 0 || qp_mineral<=0) {

    }
    else if (qp_health < qp_playerData->qp_healthMax) {

    }
if (qp_worldData->qp_temperature < qp_playerData->qp_temperatureMin) {

	qp_consumptionEnergyNow = qp_playerData->qp_energyConsumption + qp_actor->GetVelocity().Size() * qp_playerData->qp_energyConsumptionAdd;
}
else {
	qp_consumptionEnergyNow = qp_playerData->qp_energyConsumption + qp_actor->GetVelocity().Size() * qp_playerData->qp_energyConsumptionAdd;
}*/
//qp_energyToTemperature
    //qp_waterToTemperature
    //qp_humidityMin
    //qp_humidityMax
    //qp_waterToHumidity
    //qp_waterToHumidityAdd
    //qp_humidityToTemperature
//加一个world数据，填写温度湿度氧气等

//qp_energy
   

   
    /*float Damage = (ATK - DEF * 0.5f) * (FMath::FRand() < CRIT ? 2.f : 1.f);

   
    Out.AddOutputModifier(FGameplayModifierEvaluatedData(
        UMyAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, -Damage));*/
}