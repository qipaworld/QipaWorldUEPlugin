// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Widget/QPTextBlock.h"
#include "QPSimpleTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPSimpleTextBlock : public UQPTextBlock
{
	GENERATED_BODY()
public:


	/**改变字体*/
	virtual void QP_ChangeFontSlate() override;
};
