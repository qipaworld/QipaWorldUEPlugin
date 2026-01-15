// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
//#include "AbilitySystemBlueprintLibrary.h"
//#include "GameplayEffectExtension.h"
#include "Interface/QPI_InitAttributeSet.h"

#include "QPAS_BaseBuff.generated.h"

/**
 *
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPAS_BaseBuff : public UAttributeSet, public IQPI_InitAttributeSet
{
	GENERATED_BODY()
	
public:
    virtual void QPI_InitAttributeSet(AQPMonster* k) override;
	

    //UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
        //FGameplayAttributeData qp_maxHealth;
        //ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_maxHealth)
        //GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UQPAS_BaseBuff, qp_maxHealth)
        //GAMEPLAYATTRIBUTE_VALUE_GETTER(qp_maxHealth)
        //GAMEPLAYATTRIBUTE_VALUE_SETTER(qp_maxHealth)
        //GAMEPLAYATTRIBUTE_VALUE_INITTER(qp_maxHealth)


    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_NOLocal))
    FGameplayAttributeData qp_healthTask = 0;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_healthTask)

    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_NOLocal))
    FGameplayAttributeData qp_die = 0;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_die)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow, QP_ShowInformationHealth))
    FGameplayAttributeData qp_health;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_health)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation, QP_ShowInformationHealth))
    FGameplayAttributeData qp_healthRecharge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_healthRecharge)
        

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedProtein;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedProtein)

   
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedMineral)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_healthMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_healthMax)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedEnergy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedEnergy)
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedFat;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedFat)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedOxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedWater)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    FGameplayAttributeData qp_R_healthNeedTemperature;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_healthNeedTemperature)
    //-------------------------------------------------
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_sugar;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_sugar)

        // 使用脂肪恢复糖的速度
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_sugarRechargeUseFat;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_sugarRechargeUseFat)

        // 使用蛋白质恢复糖的速度
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_sugarRechargeUseProtein;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_sugarRechargeUseProtein)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_sugarMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_sugarMax)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    FGameplayAttributeData qp_sugarToEnergy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_sugarToEnergy)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    FGameplayAttributeData qp_C_sugarNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_sugarNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    FGameplayAttributeData qp_C_sugarNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_sugarNeedMineral)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    FGameplayAttributeData qp_C_sugarNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_sugarNeedOxygen)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    FGameplayAttributeData qp_C_sugarOutWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_sugarOutWater)

    //------------------------------------------------------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_protein;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_protein)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_proteinMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_proteinMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_proteinRecharge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_proteinRecharge)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_proteinToSugar;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_proteinToSugar)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_C_proteinNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_proteinNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_C_proteinOutWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_proteinOutWater)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinNeedWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinNeedWater)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_C_proteinNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_proteinNeedOxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_C_proteinNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_proteinNeedMineral)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinNeedOxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinNeedEnergy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinNeedEnergy)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinNeedMineral)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    FGameplayAttributeData qp_R_proteinMin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_proteinMin)

        //-------------------------------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNox))
    FGameplayAttributeData qp_fat;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_fat)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_fatMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_fatMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_fatRecharge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_fatRecharge)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_fatToSugar;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_fatToSugar)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_C_fatNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_fatNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_C_fatNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_fatNeedOxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_C_fatNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_fatNeedMineral)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_C_fatOutWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_C_fatOutWater)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatNeedVitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatNeedVitamin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatNeedEnergy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatNeedEnergy)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatNeedOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatNeedOxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatNeedMineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatNeedMineral)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatMin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatMin)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    FGameplayAttributeData qp_R_fatNeedWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_fatNeedWater)

    //----------------------------------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_energy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_energy)

    //UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    //FGameplayAttributeData qp_energyNeedSugar;
    //ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_energyNeedSugar)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_energyMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_energyMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_energyRecharge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_energyRecharge)

        //UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase))
    //FGameplayAttributeData qp_energyToTemperature;
    //ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_energyToTemperature)

    //------------------------------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_temperature;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperature)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_temperatureRecharge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureRecharge)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_R_temperatureNeedEnergy;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_R_temperatureNeedEnergy)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_temperatureDischarge;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureDischarge)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_D_temperatureNeedWater;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_D_temperatureNeedWater)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_temperatureMin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureMin)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_temperatureMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature, QP_ShowInformationMax))
    FGameplayAttributeData qp_temperatureMid;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureMid)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    FGameplayAttributeData qp_temperatureKeep;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_temperatureKeep)

    //----------------------------------------------
       
  
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    FGameplayAttributeData qp_aroundTemperatureMin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_aroundTemperatureMin)
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    FGameplayAttributeData qp_aroundTemperatureRange;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_aroundTemperatureRange)


    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    FGameplayAttributeData qp_aroundHumidity;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_aroundHumidity)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_humidity;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_humidity)
    //-----------------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_antitoxic = 5;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_antitoxic)

    //-------------------------------------
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_vitamin;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_vitamin)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_vitaminMax = 100;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_vitaminMax)


    //-----------------------------------------

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_oxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_oxygen)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    FGameplayAttributeData qp_aroundOxygen;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_aroundOxygen)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_oxygenMax = 100;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_oxygenMax)


    //--------------------------------------------
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_water;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_water)
       
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_waterMax = 100;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_waterMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    FGameplayAttributeData qp_waterConsume;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_waterConsume)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationWater))
    FGameplayAttributeData qp_waterToHumidity;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_waterToHumidity)


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_urineMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_urineMax)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_urine = 0;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_urine)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_excrement = 0;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_excrement)

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_excrementMax;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_excrementMax)
    //----------------------------------------
       
    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    FGameplayAttributeData qp_mineral;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_mineral)

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    FGameplayAttributeData qp_mineralMax = 100;
    ATTRIBUTE_ACCESSORS_BASIC(UQPAS_BaseBuff, qp_mineralMax)
        

    
        // 攻击力
       /* UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS_BASIC(UMyAttributeSet, AttackPower)*/

    // 用于声明哪些属性需要在网络中进行复制
            virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
        // 当Attribute的CurrentValue被改变之前调用
        //virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
        // 仅在instant Gameplay Effect使Attribute的BaseValue改变时触发
        virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

        virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

        virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

        UFUNCTION()
        void OnRep_qp_health(const FGameplayAttributeData& OldHealth);
        UFUNCTION()
        void OnRep_qp_maxHealth(const FGameplayAttributeData& OldMaxHealth);
        
        virtual void QP_HealthTask();

        UAbilitySystemComponent* qp_ASC;
        class UQPData* qp_localPlayerData_Status;
        class AQPMonster* qp_monster;
};
