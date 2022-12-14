// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Localization/QPGIM_Localization.h"
#include "Engine/Font.h"
#include "Data/QPData.h"
#include "QPTextBlock.generated.h"


/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPTextBlock : public UTextBlock
{
	GENERATED_BODY()
public:
	/**国际化文件路径*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPTextBlock")
	FString qp_fontPath = "/Script/Engine.Font'/Game/QipaWorld3D/Font/QP_Default.QP_Default'";
	/**是否根据国际化改变字体*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPTextBlock")
	bool qp_changeSlate = true;

	UQPTextBlock();

	/**监听国际化地区改变事件*/
	void QP_L10NChange(const UQPData* data);
	/**改变字体*/
	virtual void QP_ChangeFontSlate();

private:
	
};
