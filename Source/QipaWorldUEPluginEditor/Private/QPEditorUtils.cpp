// QIPAWORLD
#include "QPEditorUtils.h"
#include "EditorUtilitySubsystem.h"
#include "Editor.h"
#include "WidgetBlueprint.h"
#include "EditorUtilityLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "Widget/QPTextBlock.h"


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
						NewTextBlock->SetColorAndOpacity(OldTextBlock->ColorAndOpacity);
						NewTextBlock->SetFont(OldTextBlock->Font);
						//NewTextBlock->SetJustification(OldTextBlock->GetJustification());
						NewTextBlock->SetShadowColorAndOpacity(OldTextBlock->ShadowColorAndOpacity);
						NewTextBlock->SetShadowOffset(OldTextBlock->ShadowOffset);
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

				UPackage::SavePackage(Package, WidgetBP, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
				
			
		}
	}
	

}