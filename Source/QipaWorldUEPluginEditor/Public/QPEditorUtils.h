// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPEditorUtils.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGINEDITOR_API UQPEditorUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static void QP_ReplaceTextBlocksWithCustomSubclass();
	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static void QP_ChangeLevelAllActorsTag( FName oldTag,FName newTag);
};
