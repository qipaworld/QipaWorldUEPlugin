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
	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static void QP_ReplaceLevelActor();
	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static void QP_ReplaceLevelActorByMeshName(FName n);

	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static void QP_ResetScaleAndReImport(float scale);

	//UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	/*void QP_CreateSetTextureParameterAndApply(
		const FString& AssetName,
		const FString& PackagePath,
		UMaterialInterface* ParentMaterial,
		UTexture* NewTexture,
		const FName& TextureParamName,
		UStaticMesh* StaticMeshAsset,
		int32 MaterialIndex = 0
	);*/
	UFUNCTION(BlueprintCallable, Category = "QPEditorUtils")
	static UMaterialInstanceConstant* QP_CreateSetTextureParameterAndApply(
		UMaterialInterface* ParentMaterial,
		UTexture* NewTexture,
		UTexture* N_Texture,
		bool is_N_Texture,
		const FName& TextureParamName,
		const FName& N_TextureParamName
	);
};
