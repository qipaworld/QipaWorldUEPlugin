// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
//#include "Item/QPItem.h"
//#include "Skill/QP_SkillData.h"
#include "Item/QPDA_ItemFood.h"

#include "QPDA_ItemVegetable.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPDA_ItemVegetable : public UQPDA_ItemFood
{
	GENERATED_BODY()
	public:
	
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_sugar = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_vitamin = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
    float qp_mineral = 0;
    
};
