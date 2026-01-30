// QIPAWORLD
#include "QPEditorUtils.h"
#include "EditorUtilitySubsystem.h"
#include "Editor.h"
#include "WidgetBlueprint.h"
#include "EditorUtilityLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "EditorLevelLibrary.h"
#include "Widget/QPTextBlock.h"
#include "UObject/SavePackage.h"
#include "EngineUtils.h"
#include "Factories/FbxAssetImportData.h"
#include "Engine/StaticMeshActor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MaterialEditingLibrary.h"
#include "EditorAssetLibrary.h"
#include "Engine/Engine.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MaterialEditingLibrary.h"
#include "EditorAssetLibrary.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "Editor.h"
#include "EditorUtilityLibrary.h"
#include "Factories/FbxAssetImportData.h"
#include "Engine/SkeletalMesh.h"
#include "ObjectTools.h"
#include "EditorAssetLibrary.h"
#include "EditorReimportHandler.h"
#include "Misc/PackageName.h"
#include "Blueprint/WidgetTree.h"
#include "Widget/QPTextBlock.h"
#include "ObjectTools.h"
#include "Misc/ObjectThumbnail.h"
#include "Engine/Texture2D.h"
#include "AssetToolsModule.h"
//#include "AssetRegistryModule.h"
#include "UObject/Package.h"
#include "Engine/Texture.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "Editor.h"
#include "ImageUtils.h"
#include "Modules/ModuleManager.h"


void UQPEditorUtils::QP_ReplaceTextBlocksWithCustomSubclass()
{
	TArray< UObject* > SelectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	

	for (UObject* Asset : SelectedAssets)
	{
		if (UWidgetBlueprint* WidgetBP = Cast<UWidgetBlueprint>(Asset))
		{
			
				UWidgetTree* Tree = WidgetBP->WidgetTree;
				if (!Tree) return;

				TArray<UWidget*> AllWidgets;
				Tree->GetAllWidgets(AllWidgets);

				for (UWidget* WidgetItem : AllWidgets)
				{
					UTextBlock* OldTextBlock = Cast<UTextBlock>(WidgetItem);
					
					if (OldTextBlock && !OldTextBlock->IsA(UQPTextBlock::StaticClass()))
					{
						UQPUtil::QP_LOG_EX("Replacing TextBlock Name: %s", OldTextBlock->GetName());

						UQPTextBlock* NewTextBlock = Tree->ConstructWidget<UQPTextBlock>(UQPTextBlock::StaticClass(), FName(OldTextBlock->GetFName().ToString() + "_"));
						
						NewTextBlock->SetText(OldTextBlock->GetText());
							
					
						NewTextBlock->SetText(OldTextBlock->GetText());
						NewTextBlock->SetColorAndOpacity(OldTextBlock->GetColorAndOpacity());
						NewTextBlock->SetFont(OldTextBlock->GetFont());
						//NewTextBlock->SetJustification(OldTextBlock->GetJustification());
						NewTextBlock->SetShadowColorAndOpacity(OldTextBlock->GetShadowColorAndOpacity());
						NewTextBlock->SetShadowOffset(OldTextBlock->GetShadowOffset());
						//NewTextBlock->SetAutoWrapText(OldTextBlock->gettextwidg);
						
						if (UPanelWidget* Parent = Cast<UPanelWidget>(OldTextBlock->GetParent()))
						{
							int32 Index = Parent->GetChildIndex(OldTextBlock);
							Parent->RemoveChild(OldTextBlock);
							Parent->InsertChildAt(Index, NewTextBlock);
						}

					}
				}

				WidgetBP->MarkPackageDirty();

				UPackage* Package = WidgetBP->GetOutermost();
				FString PackageFileName = FPackageName::LongPackageNameToFilename(Package->GetName(), FPackageName::GetAssetPackageExtension());

				FSavePackageArgs SaveArgs;
				SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;

				UPackage::SavePackage(Package, WidgetBP, *PackageFileName, SaveArgs);
				
			
		}
	}
	

}

void UQPEditorUtils::QP_ChangeLevelAllActorsTag( FName oldTag, FName newTag) {
	//if (!World) return;

	
	for (TActorIterator<AActor> ActorItr(GEditor->GetEditorWorldContext().World()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		if (!Actor) continue;

		for (int i = 0; i < Actor->Tags.Num(); ++i) {
			if (Actor->Tags[i] == oldTag) {
				Actor->Tags[i] = newTag;
			}
		}
		
	}
	GEditor->GetEditorWorldContext().World()->MarkPackageDirty();
}

void UQPEditorUtils::QP_ReplaceLevelActor() {
	UClass* c = (Cast<UBlueprint>(UEditorUtilityLibrary::GetSelectedAssets()[0]))->GeneratedClass;

	TArray<AActor*> SelectedActors = UEditorLevelLibrary::GetSelectedLevelActors();
	FTransform t;
	for (auto v : SelectedActors) {
		t = v->GetTransform();
		GEditor->GetEditorWorldContext().World()->SpawnActor(c, &t);
		v->Destroy();
	}
	GEditor->GetEditorWorldContext().World()->MarkPackageDirty();

	//TArray< UObject* > SelectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
}
void UQPEditorUtils::QP_ThumbnailToTexture() {

	TArray<UObject*> qp_objs = UEditorUtilityLibrary::GetSelectedAssets();

	for (UObject* SourceAsset : qp_objs)
	{
		
			FObjectThumbnail Thumb;
			ThumbnailTools::LoadThumbnailFromPackage(SourceAsset, Thumb);

			
			IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
			UObject* NewAsset = AssetTools.CreateAsset(SourceAsset->GetName() + "_Thumbnail", FPackageName::GetLongPackagePath(SourceAsset->GetOutermost()->GetName()), UTexture2D::StaticClass(), nullptr);

			UTexture2D* NewTex = Cast<UTexture2D>(NewAsset);
			if (!NewTex) {
				return;
			}

			const int32 Width = Thumb.GetImageWidth();
			const int32 Height = Thumb.GetImageHeight();
			const TArray<uint8>& RawData = Thumb.GetUncompressedImageData();

			

			NewTex->Source.Init(
				Width,
				Height,
				1,              
				1,              
				TSF_BGRA8,      
				RawData.GetData() 
			);

			NewTex->SRGB = true;
			NewTex->MipGenSettings = TMGS_NoMipmaps;
			NewTex->CompressionSettings = TC_Default;
			//NewTex->PostEditChange();
			NewTex->UpdateResource();

	}
	

}
void UQPEditorUtils::QP_ReplaceLevelActorByMeshName(FName n) {
	UClass* c = (Cast<UBlueprint>(UEditorUtilityLibrary::GetSelectedAssets()[0]))->GeneratedClass;

	TArray<AActor*> SelectedActors = UEditorLevelLibrary::GetSelectedLevelActors();
	FTransform t;
	for (auto v : SelectedActors) {
		UStaticMeshComponent* MeshComp = v->FindComponentByClass<UStaticMeshComponent>();
		if (MeshComp)
		{
			UStaticMesh* Mesh = MeshComp->GetStaticMesh();
			if (Mesh&& Mesh->GetFName() == n)
			{
				t = v->GetTransform();
				GEditor->GetEditorWorldContext().World()->SpawnActor(c, &t);
				v->Destroy();
			}
		}
		
	}
	GEditor->GetEditorWorldContext().World()->MarkPackageDirty();
}

void UQPEditorUtils::QP_ResetScaleAndReImport(float scale)
{
	TArray<UObject*> qp_objs = UEditorUtilityLibrary::GetSelectedAssets();

	for (UObject* o : qp_objs)
	{
		if (USkeletalMesh* s = Cast<USkeletalMesh>(o)) {
			(Cast<UFbxAssetImportData>(s->GetAssetImportData()))->ImportUniformScale = scale;
		}
		else {
			FObjectProperty* Property = CastField<FObjectProperty>(o->GetClass()->FindPropertyByName("AssetImportData"));
			//QP_ChangeScale(Cast<UFbxAssetImportData>(Property->ContainerPtrToValuePtr<UAssetImportData>(o)), scale);

			if (Property) {
				UFbxAssetImportData* ass = Cast<UFbxAssetImportData>(Property->GetObjectPropertyValue_InContainer(o));
				if (ass) {
					ass->ImportUniformScale = scale;
				}
				else {
					//UQPUtil::QP_LOG();
					UQPUtil::QP_LOG(o->GetName() + " do not have UFbxAssetImportData");

				}
				//QP_ChangeScale(Cast<UFbxAssetImportData>(Property->ContainerPtrToValuePtr<UAssetImportData>(o)), scale);
			}
			else {
				UQPUtil::QP_LOG(o->GetName() + " do not have AssetImportData");
			}


		}

	}
	FReimportManager::Instance()->ReimportMultiple(qp_objs);
	UEditorAssetLibrary::SaveLoadedAssets(qp_objs, false);
}

//void UQPEditorUtils::QP_CreateSetTextureParameterAndApply(
//	const FString& AssetName,
//	const FString& PackagePath,
//	UMaterialInterface* ParentMaterial,
//	UTexture* NewTexture,
//	const FName& TextureParamName,
//	UStaticMesh* StaticMeshAsset,
//	int32 MaterialIndex = 0
//)
//{
//	if (!ParentMaterial || !NewTexture || !StaticMeshAsset)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Invalid input parameters"));
//		return;
//	}
//
//	// 创建材质实例
//	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
//	UObject* NewAsset = AssetTools.CreateAsset(AssetName, PackagePath, UMaterialInstanceConstant::StaticClass(), nullptr);
//	UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(NewAsset);
//	if (!MIC)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to create MaterialInstanceConstant asset"));
//		return;
//	}
//
//	// 设置父材质
//	UMaterialEditingLibrary::SetMaterialInstanceParent(MIC, ParentMaterial);
//
//	// 设置Texture参数（编辑器专用函数）
//	MIC->SetTextureParameterValueEditorOnly(TextureParamName, NewTexture);
//
//	// 保存材质实例资产
//	TArray<UObject*> AssetsToSave;
//	AssetsToSave.Add(MIC);
//	UEditorAssetLibrary::SaveLoadedAssets(AssetsToSave, false);
//
//	// 应用材质实例到StaticMesh指定Material槽
//	if (StaticMeshAsset->GetStaticMaterials().IsValidIndex(MaterialIndex))
//	{
//		StaticMeshAsset->SetMaterial(MaterialIndex, MIC);
//		StaticMeshAsset->MarkPackageDirty();
//		// 保存StaticMesh资产更改
//		UPackage* MeshPackage = StaticMeshAsset->GetOutermost();
//		FSavePackageArgs SaveArgs;
//		SaveArgs.TopLevelFlags = RF_Standalone;
//		UPackage::SavePackage(MeshPackage, StaticMeshAsset, *MeshPackage->GetName(), SaveArgs);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("MaterialIndex %d invalid for StaticMesh"), MaterialIndex);
//	}
//
//	UE_LOG(LogTemp, Log, TEXT("Material Instance created, texture parameter set, and applied to StaticMesh."));
//}

UMaterialInstanceConstant* UQPEditorUtils::QP_CreateSetTextureParameterAndApply(
	UMaterialInterface* ParentMaterial,
	UTexture* NewTexture,
	UTexture* N_Texture,
	bool is_N_Texture,
	const FName& TextureParamName,
	const FName& N_TextureParamName
)
{
	if (!ParentMaterial || !NewTexture)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid input parameters"));
		return nullptr;
	}
	
	// 创建材质实例
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* NewAsset = AssetTools.CreateAsset(NewTexture->GetName()+"_MI", FPackageName::GetLongPackagePath(NewTexture->GetOutermost()->GetName()), UMaterialInstanceConstant::StaticClass(), nullptr);
	UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(NewAsset);
	if (!MIC)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create MaterialInstanceConstant asset"));
		return nullptr;
	}

	// 设置父材质
	UMaterialEditingLibrary::SetMaterialInstanceParent(MIC, ParentMaterial);

	// 设置Texture参数（编辑器专用函数）
	MIC->SetTextureParameterValueEditorOnly(TextureParamName, NewTexture);
	if (is_N_Texture) {
		MIC->SetTextureParameterValueEditorOnly(N_TextureParamName, N_Texture);

	}
	// 保存材质实例资产
	//TArray<UObject*> AssetsToSave;
	//AssetsToSave.Add(MIC);
	UEditorAssetLibrary::SaveLoadedAsset(MIC, false);

	return MIC;

	//UE_LOG(LogTemp, Log, TEXT("Material Instance created, texture parameter set, and applied to StaticMesh."));
}

void UQPEditorUtils::QP_CheckStaticMeshActorsForMissingMeshes(UWorld* World)
{
	if (!World)
	{
		if (GEditor)
		{
			const FWorldContext& EditorWorldContext = GEditor->GetEditorWorldContext();
			World =  EditorWorldContext.World();
		}

		if (!World)
		{
			UQPUtil::QP_LOG(" world is missing ");
			return;
		}
	}

	for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
	{
		AStaticMeshActor* SMActor = *It;
		if (!SMActor)
		{
			continue;
		}

		UStaticMeshComponent* MeshComp = SMActor->GetStaticMeshComponent();
		if (!MeshComp)
		{
			UQPUtil::QP_LOG( SMActor->GetName() + "is missing");
			continue;
		}

		if (MeshComp->GetStaticMesh() == nullptr)
		{
			UQPUtil::QP_LOG(SMActor->GetName() + "is missing StaticMesh");


		}
	}
}