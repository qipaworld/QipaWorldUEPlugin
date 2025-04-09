// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QPObject.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "QipaWorld|Object")
	int32 qp_objId = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "QipaWorld|Object")
	FName qp_objTag;

	UFUNCTION(BlueprintPure, Category = "QipaWorld|Object")
	int32 QP_GetObjId();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Object")
	void QP_SetObjId(int32 id);

	UFUNCTION(BlueprintPure, Category = "QipaWorld|Object")
	FName QP_GetObjTag();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Object")
	void QP_SetObjTag(FName tag);
};
