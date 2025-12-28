// QIPAWORLD


#include "GamePlay/AttributeSet/QPAS_BaseBuff.h"
#include "Net/UnrealNetwork.h"
#include "QPUtil.h"
#include "Monster/QPMonster.h"
#include "World/QPWorldData.h"
#include "Character/QP_SurvivalData.h"
#include "Map/QPGIM_Map.h"
#include "Data/QPGIM_PlayerData.h"
#include "GameplayEffectExtension.h"


void UQPAS_BaseBuff::QPI_InitAttributeSet(AQPMonster* v) {

    qp_monster = v;
    qp_localPlayerData_Status = UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerData()->QP_GetUQPData("qp_localPlayerData_Status");
    UQP_SurvivalData * d = (UQP_SurvivalData*) v->qp_assetData;
    UQPWorldData* wd = UQPGIM_Map::qp_staticObject->QP_GetMapWorldData();
    //Initqp_health(v->qp_assetData->)
    qp_ASC = v->qp_abilitySystemComponent;
     Initqp_health(d->qp_healthMax);
     Initqp_healthMax(d->qp_healthMax);
     Initqp_healthRecharge(d->qp_healthRecharge);
     Initqp_R_healthNeedProtein(d->qp_R_healthNeedProtein);
     Initqp_R_healthNeedMineral(d->qp_R_healthNeedMineral);
     Initqp_R_healthNeedEnergy(d->qp_R_healthNeedEnergy);
     Initqp_R_healthNeedFat(d->qp_R_healthNeedFat);
     Initqp_R_healthNeedVitamin(d->qp_R_healthNeedVitamin);
     Initqp_R_healthNeedOxygen(d->qp_R_healthNeedOxygen);
     Initqp_R_healthNeedWater(d->qp_R_healthNeedWater);
     Initqp_R_healthNeedTemperature(d->qp_R_healthNeedTemperature);
     //-------------------------------------------------
     Initqp_sugar(d->qp_sugarMax);
     Initqp_sugarMax(d->qp_sugarMax);
     Initqp_sugarRechargeUseFat(d->qp_sugarRechargeUseFat);
     Initqp_sugarRechargeUseProtein(d->qp_sugarRechargeUseProtein);
     Initqp_sugarToEnergy(d->qp_sugarToEnergy);
     Initqp_C_sugarNeedVitamin(d->qp_C_sugarNeedVitamin);
     Initqp_C_sugarNeedOxygen(d->qp_C_sugarNeedOxygen);
     Initqp_C_sugarNeedMineral(d->qp_C_sugarNeedMineral);
     Initqp_C_sugarOutWater(d->qp_C_sugarOutWater);


     //------------------------------------------------------------------------------------
     Initqp_protein(d->qp_proteinMax);
     Initqp_proteinMax(d->qp_proteinMax);
     Initqp_proteinToSugar(d->qp_proteinToSugar);
     Initqp_proteinRecharge(d->qp_proteinRecharge);
     Initqp_C_proteinNeedVitamin(d->qp_C_proteinNeedVitamin);
     Initqp_C_proteinNeedMineral(d->qp_C_proteinNeedMineral);
     Initqp_C_proteinOutWater(d->qp_C_proteinOutWater);
     Initqp_R_proteinNeedWater(d->qp_R_proteinNeedWater);
     Initqp_C_proteinNeedOxygen(d->qp_C_proteinNeedOxygen);
     Initqp_R_proteinNeedVitamin(d->qp_R_proteinNeedVitamin);
     Initqp_R_proteinNeedMineral(d->qp_R_proteinNeedMineral);
     Initqp_R_proteinNeedOxygen(d->qp_R_proteinNeedOxygen);
     Initqp_R_proteinNeedEnergy(d->qp_R_proteinNeedEnergy);
     Initqp_R_proteinMin(d->qp_R_proteinMin);
     //-------------------------------------------------------------
     Initqp_fat(d->qp_fatMax);
     Initqp_fatMax(d->qp_fatMax);
     Initqp_fatToSugar(d->qp_fatToSugar);
     Initqp_fatRecharge(d->qp_fatRecharge);
     Initqp_C_fatNeedVitamin(d->qp_C_fatNeedVitamin);
     Initqp_C_fatNeedOxygen(d->qp_C_fatNeedOxygen);
     Initqp_C_fatNeedMineral(d->qp_C_fatNeedMineral);
     Initqp_C_fatOutWater(d->qp_C_fatOutWater);
     Initqp_R_fatNeedWater(d->qp_R_fatNeedWater);
     Initqp_R_fatNeedVitamin(d->qp_R_fatNeedVitamin);
     Initqp_R_fatNeedOxygen(d->qp_R_fatNeedOxygen);
     Initqp_R_fatNeedMineral(d->qp_R_fatNeedMineral);
     Initqp_R_fatNeedEnergy(d->qp_R_fatNeedEnergy);
     Initqp_R_fatMin(d->qp_R_fatMin);

     //----------------------------------------------------------------
     Initqp_energy(d->qp_energyMax);
     //Initqp_energyNeedSugar(d->qp_energyNeedSugar);
     Initqp_energyMax(d->qp_energyMax);
     Initqp_energyRecharge(d->qp_energyRecharge);
     //Initqp_energyToTemperature(d->qp_energyToTemperature);
     //------------------------------------------------------------
     Initqp_temperature(d->qp_temperatureMid);
     Initqp_temperatureMid(d->qp_temperatureMid);
     Initqp_temperatureRecharge(d->qp_temperatureRecharge);
     Initqp_temperatureDischarge(d->qp_temperatureDischarge);
     Initqp_R_temperatureNeedEnergy(d->qp_R_temperatureNeedEnergy);
     Initqp_D_temperatureNeedWater(d->qp_D_temperatureNeedWater);
     Initqp_temperatureMin(d->qp_temperatureMin);
     Initqp_temperatureMax(d->qp_temperatureMax);
     Initqp_temperatureKeep(d->qp_temperatureKeep);

     Initqp_humidity(d->qp_humidity);
     if (wd) {
     Initqp_aroundTemperatureMin(wd->qp_temperatureMin);
     Initqp_aroundTemperatureRange(wd->qp_temperatureRange);

     Initqp_aroundHumidity(wd->qp_humidity);
     Initqp_aroundOxygen(wd->qp_oxygen);

     }
     //----------------------------------------------

     //-----------------------------------------------

     Initqp_antitoxic(d->qp_antitoxic);

     //-------------------------------------
     Initqp_vitamin(d->qp_vitaminMax);
     Initqp_vitaminMax(d->qp_vitaminMax);
     //-----------------------------------------
     Initqp_oxygen(d->qp_oxygenMax);
     Initqp_oxygenMax(d->qp_oxygenMax);
     //--------------------------------------------
     Initqp_water(d->qp_waterMax);
     Initqp_waterToHumidity(d->qp_waterToHumidity);
     Initqp_waterConsume(d->qp_waterConsume);
     Initqp_waterMax(d->qp_waterMax);

     Initqp_urine(0);
     Initqp_urineMax(d->qp_urineMax);

     Initqp_excrement(0);
     Initqp_excrementMax(d->qp_excrementMax);
     //----------------------------------------
     Initqp_mineral(d->qp_mineralMax);
     Initqp_mineralMax(d->qp_mineralMax);

}
void UQPAS_BaseBuff::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME_CONDITION_NOTIFY(UQPAS_BaseBuff, qp_health, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UQPAS_BaseBuff, qp_maxHealth, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

//void UQPAS_BaseBuff::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
//{
//	Super::PreAttributeChange(Attribute, NewValue);
//	/*if (Attribute == GetHealthAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
//	}*/
//}
void UQPAS_BaseBuff::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute,OldValue,NewValue);
    /*if (Attribute == GetMaxHealthAttribute())
    {
        SetHealth(FMath::Min(GetHealth(), NewValue));
    }*/
    
    //if (Attribute == Getqp_excrementAttribute()) {
    //    UQPUtil::QP_LOG_EX("PostAttributeChange %d", Getqp_excrement());
    //    UQPUtil::QP_LOG_EX("PostAttributeChange %d", qp_excrement.GetBaseValue());
    //   /* if (NewValue <= 0) {
    //    UQPUtil::QP_LOG_EX("healthTask__ %d", healthTask__);
    //    }*/
    //}

    if (NewValue <= 0) {
        if (Attribute == Getqp_waterAttribute() 
            || Attribute == Getqp_healthAttribute()
            || Attribute == Getqp_oxygenAttribute()
            || Attribute == Getqp_proteinAttribute()
            || Attribute == Getqp_mineralAttribute()
            || Attribute == Getqp_fatAttribute()
            || Attribute == Getqp_vitaminAttribute()
            || Attribute == Getqp_sugarAttribute()
            || Attribute == Getqp_energyAttribute()) 
        {

            Setqp_die(1.f);
        }
    }
    
    else  if (Attribute == Getqp_temperatureAttribute()) {

        if (NewValue < Getqp_temperatureMin() || NewValue > Getqp_temperatureMax()) {
            Setqp_die(1.f);
        }
    }else if (Attribute == Getqp_oxygenAttribute()) {

        if (NewValue > Getqp_oxygenMax()*1.1 ) {
            Setqp_oxygen(Getqp_oxygenMax() * 1.1);
        }
    }
    else if (Attribute == Getqp_waterAttribute()) {

        if (NewValue > Getqp_waterMax() * 1.1) {
            
            Setqp_urine(Getqp_urine() +  (NewValue - Getqp_waterMax() * 1.1));
            Setqp_water(Getqp_waterMax() * 1.1);
        }
    }/*
    else if (Attribute == Getqp_temperatureMidAttribute()) {
        Setqp_temperatureMid((d->qp_temperatureMax - d->qp_temperatureMin) * 0.5 + d->qp_temperatureMin);

    }*/
    if (Attribute == Getqp_dieAttribute()) {
        qp_localPlayerData_Status->QP_Addfloat("qp_die", NewValue);
    }
}
void UQPAS_BaseBuff::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const {
    Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
   
    
    //if (Attribute == Getqp_excrementAttribute()) {
        //UQPUtil::QP_LOG_EX("PostAttributeBaseChange %d", Getqp_excrement());
        //UQPUtil::QP_LOG_EX("PostAttributeBaseChange %d", qp_excrement.GetBaseValue());
        /* if (NewValue <= 0) {
         UQPUtil::QP_LOG_EX("healthTask__ %d", healthTask__);
         }*/
   // }
}

void UQPAS_BaseBuff::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    //if (Data.EvaluatedData.Attribute == Getqp_excrementAttribute()) {
    //    UQPUtil::QP_LOG_EX("PostGameplayEffectExecute %d", Getqp_excrement());
    //    UQPUtil::QP_LOG_EX("PostGameplayEffectExecute %d", qp_excrement.GetBaseValue());
    //    /* if (NewValue <= 0) {
    //     UQPUtil::QP_LOG_EX("healthTask__ %d", healthTask__);
    //     }*/
    //}

	//UQPUtil::QP_LOG_EX("Getqp_health : " , Getqp_health());
	if (Data.EvaluatedData.Attribute == Getqp_healthTaskAttribute())
	{
		//SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
		//UQPUtil::QP_LOG_EX("Getqp_healthTask : ", Getqp_healthTask()); 
        QP_HealthTask();
		/*float f = Getqp_healthTask();
		UE_LOG(LogTemp, Warning, TEXT("Getqp_healthTask %f"), f);
		Initqp_health(Getqp_health() + 5);

		 f = Getqp_health();

		UE_LOG(LogTemp, Warning, TEXT("Getqp_health %f"), f);*/
	}
	//if (Data.EvaluatedData.Attribute == Getqp_healthAttribute())
	//{
	//	//SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	//	//Initqp_health(Getqp_health() + 5);
	//	float f = Getqp_health();

	//	UE_LOG(LogTemp, Warning, TEXT("Getqp_health %f"), f);

	//	//UQPUtil::QP_LOG_EX("Getqp_health : ", Getqp_health());
	//}
    //if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    //{
    //    // 比如做血量上限判断
    //    Health = FMath::Clamp(Health, 0.f, MaxHealth);
    //}
    //if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    //{
    //    // 限制范围
    //    Health.SetCurrentValue(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

    //    // 通知 UI（手动广播）
    //    OnHealthChangeDelegate.Broadcast(GetHealth(), GetMaxHealth());
    //}
}
void UQPAS_BaseBuff::QP_HealthTask() {

    float healthTask__ = Getqp_healthTask();

    
    float health__ = Getqp_health();
    float R_healthNeedProtein__ = Getqp_R_healthNeedProtein();
    float healthRecharge__ = Getqp_healthRecharge() * healthTask__;
    float R_healthNeedMineral__ = Getqp_R_healthNeedMineral();
    float healthMax__ = Getqp_healthMax();
    float R_healthNeedEnergy__ = Getqp_R_healthNeedEnergy();
    float R_healthNeedFat__ = Getqp_R_healthNeedFat();
    float R_healthNeedVitamin__ = Getqp_R_healthNeedVitamin();
    float R_healthNeedOxygen__ = Getqp_R_healthNeedOxygen();
    float R_healthNeedWater__ = Getqp_R_healthNeedWater();
    float R_healthNeedTemperature__ = Getqp_R_healthNeedTemperature();
    //-------------------------------------------------
    float sugar__ = Getqp_sugar();
    float sugarMax__ = Getqp_sugarMax();
    float sugarToEnergy__ = Getqp_sugarToEnergy();
    float sugarRechargeUseFat__ = Getqp_sugarRechargeUseFat() * healthTask__;
    float sugarRechargeUseProtein__ = Getqp_sugarRechargeUseProtein() * healthTask__;
    float C_sugarNeedVitamin__ = Getqp_C_sugarNeedVitamin();
    float C_sugarNeedOxygen__ = Getqp_C_sugarNeedOxygen();
    float C_sugarNeedMineral__ = Getqp_C_sugarNeedMineral();
    float C_sugarOutWater__ = Getqp_C_sugarOutWater();

    //加入尿和屎，水多了变成尿，

    //------------------------------------------------------------------------------------
    float protein__ = Getqp_protein();
    float proteinMax__ = Getqp_proteinMax();
    float proteinRecharge__ = Getqp_proteinRecharge() * healthTask__;
    float proteinToSugar__ = Getqp_proteinToSugar();
    float C_proteinNeedVitamin__ = Getqp_C_proteinNeedVitamin();
    float C_proteinNeedMineral__ = Getqp_C_proteinNeedMineral();
    float C_proteinNeedOxygen__ = Getqp_C_proteinNeedOxygen();
    float C_proteinOutWater__ = Getqp_C_proteinOutWater();
    float R_proteinNeedWater__ = Getqp_R_proteinNeedWater();
    float R_proteinNeedVitamin__ = Getqp_R_proteinNeedVitamin();
    float R_proteinNeedMineral__ = Getqp_R_proteinNeedMineral();
    float R_proteinNeedOxygen__ = Getqp_R_proteinNeedOxygen();
    float R_proteinNeedEnergy__ = Getqp_R_proteinNeedEnergy();
    float R_proteinMin__ = Getqp_R_proteinMin();
    //-------------------------------------------------------------
    float fat__ = Getqp_fat();
    float fatMax__ = Getqp_fatMax();
    float fatToSugar__ = Getqp_fatToSugar();
    float fatRecharge__ = Getqp_fatRecharge() * healthTask__;
    float C_fatNeedVitamin__ = Getqp_C_fatNeedVitamin();
    float C_fatNeedMineral__ = Getqp_C_fatNeedMineral();
    float C_fatNeedOxygen__ = Getqp_C_fatNeedOxygen();
    float C_fatOutWater__ = Getqp_C_fatOutWater();
    float R_fatNeedWater__ = Getqp_R_fatNeedWater();
    float R_fatNeedVitamin__ = Getqp_R_fatNeedVitamin();
    float R_fatNeedMineral__ = Getqp_R_fatNeedMineral();
    float R_fatNeedOxygen__ = Getqp_R_fatNeedOxygen();
    float R_fatNeedEnergy__ = Getqp_R_fatNeedEnergy();
    float R_fatMin__ = Getqp_R_fatMin();
    //----------------------------------------------------------------


    float energy__ = Getqp_energy();
    //float energyNeedSugar__ = Getqp_energyNeedSugar();
    float energyMax__ = Getqp_energyMax();
    float energyRecharge__ = Getqp_energyRecharge() * healthTask__;
    //float energyToTemperature__ = Getqp_energyToTemperature();

   
    //------------------------------------------------------------
    float temperature__ = Getqp_temperature();
    float temperatureRecharge__ = Getqp_temperatureRecharge() * healthTask__;
    float temperatureDischarge__ = Getqp_temperatureDischarge() * healthTask__;
    float temperatureMid__ = Getqp_temperatureMid();
    float temperatureMin__ = Getqp_temperatureMin();
    float temperatureMax__ = Getqp_temperatureMax();
    float temperatureKeep__ = Getqp_temperatureKeep();
    float R_temperatureNeedEnergy__ = Getqp_R_temperatureNeedEnergy();
    float D_temperatureNeedWater__ = Getqp_D_temperatureNeedWater();


    //----------------------------------------------
    float humidity__ = Getqp_humidity();
    float aroundHumidity__ = Getqp_aroundHumidity();
   

    //-----------------------------------------------

    float antitoxic__ = Getqp_antitoxic();

    //-------------------------------------
    float vitamin__ = Getqp_vitamin();
    float vitaminMax__ = Getqp_vitaminMax();
    //-----------------------------------------
    float oxygen__ = Getqp_oxygen();
    float aroundOxygen__ = Getqp_aroundOxygen();
    float oxygenMax__ = Getqp_oxygenMax();
    //--------------------------------------------
    float water__ = Getqp_water();
    float waterConsume__ = Getqp_waterConsume() * healthTask__;
    float waterToHumidity__ = Getqp_waterToHumidity() * healthTask__;
    float urine__ = Getqp_urine();
    float urineMax__ = Getqp_urineMax();
    float excrement__ = Getqp_excrement();
    float excrementMax__ = Getqp_excrementMax();
    float waterMax__ = Getqp_waterMax();
    //----------------------------------------
    float mineral__ = Getqp_mineral();
    float mineralMax__ = Getqp_mineralMax();
    
   
    water__ -= waterConsume__;
    
    

    urine__ += waterConsume__;

    oxygen__ += (aroundOxygen__ * healthTask__);

   
    //UQPUtil::QP_LOG_EX("PostAttributeChange %d", water__);
    
    if (aroundHumidity__ < humidity__) {
        water__ -= ((aroundHumidity__ - humidity__) * healthTask__ * waterToHumidity__);
    }
    //UQPUtil::QP_LOG_EX("aroundTemperature__ %d", aroundTemperature__);
    //UQPUtil::QP_LOG_EX("temperature__ %d", temperature__);
    //UQPUtil::QP_LOG_EX("NeedWater %d", NeedWater);

    //float aroundTemperature__ = ;
   
    temperature__ += ((Getqp_aroundTemperatureMin() + Getqp_aroundTemperatureRange()* UQPGIM_Map::qp_staticObject->qp_mapTimeEx - temperature__) * healthTask__ * (1 - temperatureKeep__));

    //UQPUtil::QP_LOG_EX("temperature__ %d", temperature__);

    
   
    if (temperature__ < temperatureMid__) {
        
        float NeedEnergy = temperatureRecharge__ * R_temperatureNeedEnergy__;
        if (NeedEnergy < energy__) {
            energy__ -= NeedEnergy;
            temperature__ +=( temperatureRecharge__ - (temperatureRecharge__ *  aroundHumidity__*0.5));
        }
    }
    else if (temperature__ > temperatureMid__) {
        float NeedWater = temperatureDischarge__ * D_temperatureNeedWater__;
        if (NeedWater < water__) {
            water__ -= NeedWater;
            //UQPUtil::QP_LOG_EX("NeedWater %d", NeedWater);
            temperature__ += (temperatureDischarge__ *(1- aroundHumidity__));
        }
    }

    


    
    
    if (fat__ < fatMax__ && fat__ / fatMax__ < R_fatMin__) {
        float NeedVitamin = R_fatNeedVitamin__ * fatRecharge__;
        float NeedOxygen = R_fatNeedOxygen__ * fatRecharge__;
        float NeedMineral = R_fatNeedMineral__ * fatRecharge__;
        float NeedEnergy = R_fatNeedEnergy__ * fatRecharge__;
        float NeedWater = R_fatNeedWater__ * fatRecharge__;
        
        if (mineral__ > NeedMineral &&
            vitamin__ > NeedVitamin &&
            energy__ > NeedEnergy &&
            water__ > NeedWater &&
            oxygen__ > NeedOxygen) {

            mineral__ -= NeedMineral;
            vitamin__ -= NeedVitamin;
            oxygen__ -= NeedOxygen;
            energy__ -= NeedEnergy;
            water__ -= NeedWater;
            
            fat__ += fatRecharge__;
        }
    }else if (sugar__ < sugarMax__) {
        float needFat = sugarRechargeUseFat__ / fatToSugar__;
        float NeedVitamin = C_fatNeedVitamin__ * needFat;
        float NeedOxygen = C_fatNeedOxygen__ * needFat;
        float NeedMineral = C_fatNeedMineral__ * needFat;
        float OutWater = C_fatOutWater__ * needFat;

        if (fat__ > needFat &&
            mineral__ > NeedMineral &&
            vitamin__ > NeedVitamin &&
            oxygen__ > NeedOxygen) {

            fat__ -= needFat;
            mineral__ -= NeedMineral;
            vitamin__ -= NeedVitamin;
            oxygen__ -= NeedOxygen;
            sugar__ += sugarRechargeUseFat__;
            water__ += OutWater;
        }

    }
    
    if (protein__ < proteinMax__ && protein__ / proteinMax__ < R_proteinMin__) {
        float NeedVitamin = R_proteinNeedVitamin__ * proteinRecharge__;
        float NeedOxygen = R_proteinNeedOxygen__ * proteinRecharge__;
        float NeedMineral = R_proteinNeedMineral__ * proteinRecharge__;
        float NeedEnergy = R_proteinNeedEnergy__ * proteinRecharge__;
        float NeedWater = R_proteinNeedWater__ * proteinRecharge__;
       
        if (mineral__ > NeedMineral &&
            vitamin__ > NeedVitamin &&
            energy__ > NeedEnergy &&
            water__ > NeedWater &&
            oxygen__ > NeedOxygen) {

            mineral__ -= NeedMineral;
            vitamin__ -= NeedVitamin;
            oxygen__ -= NeedOxygen;
            energy__ -= NeedEnergy;
            water__ -= NeedWater;
            
            protein__ += proteinRecharge__;

        }

    }else if (sugar__ < sugarMax__) {
        float NeedProtein = sugarRechargeUseProtein__ / proteinToSugar__;
        float NeedVitamin = C_proteinNeedVitamin__ * NeedProtein;
        float NeedOxygen = C_proteinNeedOxygen__ * NeedProtein;
        float NeedMineral = C_proteinNeedMineral__ * NeedProtein;
        float OutWater = C_proteinOutWater__ * NeedProtein;

        if (protein__ > NeedProtein &&
            mineral__ > NeedMineral &&
            vitamin__ > NeedVitamin &&
            oxygen__ > NeedOxygen) {

            protein__ -= NeedProtein;
            mineral__ -= NeedMineral;
            vitamin__ -= NeedVitamin;
            oxygen__ -= NeedOxygen;
            sugar__ += sugarRechargeUseProtein__;
            water__ += OutWater;


        }

    }
    
    if (energy__ < energyMax__) {

        float needSugar = energyRecharge__ / sugarToEnergy__;
        float NeedVitamin = C_sugarNeedVitamin__ * needSugar;
        float NeedOxygen = C_sugarNeedOxygen__ * needSugar;
        float NeedMineral = C_sugarNeedMineral__ * needSugar;
        float OutWater = C_sugarOutWater__ * needSugar;
     
        if (sugar__ > needSugar && NeedVitamin < vitamin__ && NeedOxygen < oxygen__ && mineral__ > NeedMineral) {
            vitamin__ -= NeedVitamin;
            oxygen__ -= NeedOxygen;
            mineral__ -= NeedMineral;
            sugar__ -= needSugar;
            energy__ += energyRecharge__;
            water__ += OutWater;

        }
        
    }

   

    
    if (health__ < healthMax__) {

        float needEnergy = healthRecharge__ * R_healthNeedEnergy__;
        float NeedProtein = healthRecharge__ * R_healthNeedProtein__;
        float NeedMineral = healthRecharge__ * R_healthNeedMineral__;
        float NeedFat = healthRecharge__ * R_healthNeedFat__;
        float NeedVitamin = healthRecharge__ * R_healthNeedVitamin__;
        float NeedOxygen = healthRecharge__ * R_healthNeedOxygen__;
        float NeedWater = healthRecharge__ * R_healthNeedWater__;
        float NeedTemperature = healthRecharge__ * R_healthNeedTemperature__;
        if (energy__ > needEnergy &&
            protein__ > NeedProtein &&
            mineral__ > NeedMineral &&
            fat__ > NeedFat &&
            vitamin__ > NeedVitamin &&
            oxygen__ > NeedOxygen &&
            water__ > NeedWater &&
            temperature__ > NeedTemperature) {

                energy__ -= needEnergy;
                protein__ -= NeedProtein;
                mineral__ -= NeedMineral;
                fat__ -= NeedFat;
                vitamin__ -= NeedVitamin;
                oxygen__ -= NeedOxygen;
                water__ -= NeedWater;
                temperature__ -= NeedTemperature;
                health__ += healthRecharge__;

        }
    }
    
    //Setqp_excrement(excrement__);
    /*qp_health.SetCurrentValue(health__);
    qp_sugar.SetCurrentValue(sugar__);
    qp_protein.SetCurrentValue(protein__);
    qp_fat.SetCurrentValue(fat__);
    qp_energy.SetCurrentValue(energy__);
    qp_temperature.SetCurrentValue(temperature__);
    qp_vitamin.SetCurrentValue(vitamin__);
    qp_oxygen.SetCurrentValue(oxygen__);
    qp_water.SetCurrentValue(water__);*/
    //qp_urine.SetCurrentValue(urine__);
    //qp_excrement.SetCurrentValue(excrement__);
    //qp_mineral.SetCurrentValue(mineral__);
    if (qp_monster->Controller&&qp_monster->Controller->IsLocalPlayerController()) {
        qp_localPlayerData_Status->QP_Addfloat("qp_excrement", excrement__);
        qp_localPlayerData_Status->QP_Addfloat("qp_health", health__);
        qp_localPlayerData_Status->QP_Addfloat("qp_sugar", sugar__);
        qp_localPlayerData_Status->QP_Addfloat("qp_protein", protein__);
        qp_localPlayerData_Status->QP_Addfloat("qp_fat", fat__);
        qp_localPlayerData_Status->QP_Addfloat("qp_energy", energy__);
        qp_localPlayerData_Status->QP_Addfloat("qp_temperature", temperature__);
        qp_localPlayerData_Status->QP_Addfloat("qp_vitamin", vitamin__);
        qp_localPlayerData_Status->QP_Addfloat("qp_oxygen", oxygen__);
        qp_localPlayerData_Status->QP_Addfloat("qp_water", water__);
        qp_localPlayerData_Status->QP_Addfloat("qp_urine", urine__);
        qp_localPlayerData_Status->QP_Addfloat("qp_mineral", mineral__);

        qp_localPlayerData_Status->QP_Addfloat("qp_excrementMax", excrementMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_healthMax", healthMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_sugarMax", sugarMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_proteinMax", proteinMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_fatMax", fatMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_energyMax", energyMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_temperatureMax", temperatureMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_vitaminMax", vitaminMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_oxygenMax", oxygenMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_waterMax", waterMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_urineMax", urineMax__);
        qp_localPlayerData_Status->QP_Addfloat("qp_mineralMax", mineralMax__);
    }
    

    if (qp_ASC)
    {
        //qp_ASC->ForceReplication();
        qp_ASC->SetNumericAttributeBase(Getqp_excrementAttribute(), excrement__);
        qp_ASC->SetNumericAttributeBase(Getqp_healthAttribute(),health__);
        qp_ASC->SetNumericAttributeBase(Getqp_sugarAttribute(),sugar__);
        qp_ASC->SetNumericAttributeBase(Getqp_proteinAttribute(),protein__);
        qp_ASC->SetNumericAttributeBase(Getqp_fatAttribute(),fat__);
        qp_ASC->SetNumericAttributeBase(Getqp_energyAttribute(),energy__);
        qp_ASC->SetNumericAttributeBase(Getqp_temperatureAttribute(),temperature__);
        qp_ASC->SetNumericAttributeBase(Getqp_vitaminAttribute(),vitamin__);
        qp_ASC->SetNumericAttributeBase(Getqp_oxygenAttribute(),oxygen__);
        qp_ASC->SetNumericAttributeBase(Getqp_waterAttribute(),water__);
        qp_ASC->SetNumericAttributeBase(Getqp_urineAttribute(),urine__);
        qp_ASC->SetNumericAttributeBase(Getqp_mineralAttribute(),mineral__);

    }
}
void UQPAS_BaseBuff::OnRep_qp_health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQPAS_BaseBuff, qp_health, OldHealth);
}

void UQPAS_BaseBuff::OnRep_qp_maxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY(UQPAS_BaseBuff, qp_maxHealth, OldMaxHealth);
}