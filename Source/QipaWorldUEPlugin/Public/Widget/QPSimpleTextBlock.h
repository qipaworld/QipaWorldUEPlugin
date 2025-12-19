// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Widget/QPTextBlock.h"
//#include "Fonts/CompositeFont.h"
//#include "Templates/SharedPointer.h"
//#include "UObject/SoftObjectPtr.h"
#include "QPSimpleTextBlock.generated.h"

/**
 * 简单的根据国际化变化的字体，
 * 他们使用同一个字体的不同标签变换字体
 * 字体标签名字必须和国际化地区标签一致
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSimpleTextBlock : public UQPTextBlock
{
	GENERATED_BODY()
public:

	/**改变字体*/
	//virtual void QP_ChangeFontSlate() override;
};
