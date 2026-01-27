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
	bool qp_isBind;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	UQPData* qp_data;
	//void QP_Init(FName n,bool b)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	FText qp_nameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	UTexture2D* qp_texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	float qp_max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	float qp_min = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	float qp_now;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")

	bool qp_isShowSelf;
};
