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
#include "Blueprint/WidgetTree.h"
#include "Widget/QPTextBlock.h"



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