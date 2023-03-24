// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Localization/QPGIM_Localization.h"
#include "Engine/Font.h"
#include "Data/QPData.h"
#include "QPTextBlock.generated.h"


/**
 * 可以改变字体的国际化文本
 * 字体必须存放在QPL10N对应的国际标签的文件夹下
 * 他会根据已选择的字体自动更换与已选择的字体相同目录下的国际化字体。
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPTextBlock : public UTextBlock
{
	GENERATED_BODY()
public:
	/**国际化文件路径*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPTextBlock")
	FString qp_fontPath = "";
	/**是否根据国际化改变字体*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPTextBlock")
	bool qp_changeSlate = true;

	UQPTextBlock();

	/**监听国际化地区改变事件*/
	void QP_L10NChange(UQPData* data);
	/**改变字体*/
	virtual void QP_ChangeFontSlate();
	UFUNCTION()
	void QP_Init();
private:
	
};
