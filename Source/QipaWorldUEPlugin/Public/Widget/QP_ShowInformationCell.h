// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/QPData.h"

#include "QP_ShowInformationCell.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQP_ShowInformationCell : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	FName qp_dataName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	bool qp_isMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	UQPData* qp_data;
	//void QP_Init(FName n,bool b)
	
};
