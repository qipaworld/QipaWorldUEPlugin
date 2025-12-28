// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Character/QPDA_Character.h"


#include "QP_SurvivalData.generated.h"

UCLASS()
class QIPAWORLDUEPLUGIN_API UQP_SurvivalData : public UQPDA_Character
{
	GENERATED_BODY()
	public:

	//-----------Health----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_healthMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_healthRecharge = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedProtein = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedMineral = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedEnergy = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedFat = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedVitamin = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedOxygen = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedWater = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_healthNeedTemperature = 6;
	

	//-----------suger----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_sugarMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_sugarToEnergy = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_sugarRechargeUseFat = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_sugarRechargeUseProtein = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_sugarNeedVitamin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_sugarNeedMineral = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_sugarNeedOxygen = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_sugarOutWater = 2;


	//-----------protein----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_proteinMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_proteinToSugar = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_proteinRecharge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_proteinNeedVitamin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_proteinNeedMineral = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_proteinNeedOxygen = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinNeedVitamin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinNeedMineral = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinNeedOxygen = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinNeedEnergy = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinMin = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_proteinOutWater = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_proteinNeedWater = 3;
	
	//-----------fat----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_fatMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_fatRecharge = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_fatToSugar = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_fatNeedVitamin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_fatNeedMineral = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_fatNeedOxygen = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_C_fatOutWater = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatNeedWater = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatNeedVitamin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatNeedMineral = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatNeedOxygen = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatNeedEnergy = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_fatMin = 0.5;

	//-----------Energy----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_energyMax = 100;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	//float qp_energyNeedSugar = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_energyRecharge = 5;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Monster")
	//float qp_energyToTemperature = 9;


	//-----------Temperature----------
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	//float qp_waterToTemperature = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureMin = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureMax = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureMid = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureRecharge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_R_temperatureNeedEnergy = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureDischarge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_D_temperatureNeedWater = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_temperatureKeep = 0.9;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_humidity = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	//float qp_aroundHumidity = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	//float qp_aroundTemperature = 1;
	//-----------antitoxic----------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_antitoxic = 5;


	
	

	//-----------vitamin----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_vitaminMax = 100;

	//-----------oxygen----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_oxygenMax = 100;

	//-----------water----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_waterMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_waterConsume = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_waterToHumidity = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_urineMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_excrementMax = 100;

		
	//-----------mineral----------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_mineralMax = 100;

	
};
