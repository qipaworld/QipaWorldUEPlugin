// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
//#include "Item/QPItem.h"
//#include "Skill/QP_SkillData.h"
#include "Item/QPDA_ItemFood.h"

#include "QPDA_ItemMeat.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDA_ItemMeat : public UQPDA_ItemFood
{
	GENERATED_BODY()
	public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
        float qp_protein = 0;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
        float qp_fat = 0;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
        float qp_vitamin = 0;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
        float qp_mineral = 0;
	/*UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow, QP_ShowInformationHealth))
    float qp_health = 0;

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_healthMax = 0;

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation, QP_ShowInformationHealth))
    float qp_healthRecharge = 0;
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedEnergy = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedWater = 0;

    UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedProtein = 0;
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedFat = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedVitamin = 0;
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedMineral = 0;
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedTemperature = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationHealth))
    float qp_R_healthNeedOxygen = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_energy = 0;
       
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_energyMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_energyRecharge = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_temperature = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_temperatureMin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature, QP_ShowInformationMax))
    float qp_temperatureMid = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_temperatureMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_temperatureKeep = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_temperatureRecharge = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_R_temperatureNeedEnergy = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_temperatureDischarge = 0;

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationTemperature))
    float qp_D_temperatureNeedWater = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_sugar = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_sugarMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    float qp_sugarToEnergy = 0;
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_sugarRechargeUseFat = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_sugarRechargeUseProtein = 0;
    

       

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    float qp_C_sugarNeedVitamin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    float qp_C_sugarNeedMineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    float qp_C_sugarNeedOxygen = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationSuger))
    float qp_C_sugarOutWater = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_protein = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_proteinMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_proteinRecharge = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_proteinToSugar = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_C_proteinNeedVitamin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_C_proteinNeedMineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_C_proteinNeedOxygen = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_C_proteinOutWater = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinMin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinNeedEnergy = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinNeedWater = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinNeedVitamin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinNeedMineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationProtein))
    float qp_R_proteinNeedOxygen = 0;


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNox))
    float qp_fat = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_fatMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_fatRecharge = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_fatToSugar = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_C_fatNeedVitamin = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_C_fatNeedMineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_C_fatNeedOxygen = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_C_fatOutWater = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatMin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatNeedEnergy = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatNeedWater = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatNeedVitamin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatNeedMineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationFat))
    float qp_R_fatNeedOxygen = 0;
    
      
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_water = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_waterMax = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_waterConsume = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationWater))
    float qp_waterToHumidity = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    float qp_aroundTemperatureMin;
    
        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    float qp_aroundTemperatureRange;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    float qp_aroundHumidity;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_vitamin = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_vitaminMax  = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_mineral = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_mineralMax = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_oxygen = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes")
    float qp_aroundOxygen;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_oxygenMax  = 0;
    


      

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_humidity = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformation))
    float qp_antitoxic  = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_urine = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_urineMax = 0;
    


        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalData, QP_ShowInformationNow))
    float qp_excrement = 0;
    

        UPROPERTY(BlueprintReadOnly, Category = "QipaWorld|Attributes", meta = (QP_LocalDataBase, QP_ShowInformationMax))
    float qp_excrementMax = 0;*/
    
};
