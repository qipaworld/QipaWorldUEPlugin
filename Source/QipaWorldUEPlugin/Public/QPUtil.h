// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPUtil.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Return true if the object is usable : non-null and not pending kill
	UFUNCTION(BlueprintPure, Category = "QPUtil")
	static FIntPoint QP_GetFullScreenResolution(float percentage = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "QPUtil")

	static void QP_UpdateMouse(UObject* Context,bool b);

};
