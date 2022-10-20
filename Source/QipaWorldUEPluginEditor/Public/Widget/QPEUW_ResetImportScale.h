// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "QPEUW_ResetImportScale.generated.h"

class UFbxAssetImportData;
/**
*重新设置导入的缩放
*/
UCLASS()
class QIPAWORLDUEPLUGINEDITOR_API UQPEUW_ResetImportScale : public UEditorUtilityWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void QP_ResetScaleAndReImport(float scale);

	void QP_ChangeScale(UFbxAssetImportData* AssetImportData,float scale);
};
