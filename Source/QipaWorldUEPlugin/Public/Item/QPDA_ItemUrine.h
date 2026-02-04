// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
//#include "Item/QPItem.h"
//#include "Skill/QP_SkillData.h"
#include "Item/QPDA_ItemMeat.h"

#include "QPDA_ItemUrine.generated.h"

/**
 *
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDA_ItemUrine : public UQPDA_ItemMeat
{
	GENERATED_BODY()
	public:
	
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
      float qp_outWaterProportion = 0.1;


       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outVitaminProportion = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outMineralProportion = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outSugarProportion = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outProteinProportion = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outFatProportion = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_outPoisonProportion = 0;

 


    
};
