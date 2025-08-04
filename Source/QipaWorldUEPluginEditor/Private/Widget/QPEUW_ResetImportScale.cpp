// QIPAWORLD


#include "Widget/QPEUW_ResetImportScale.h"
#include "EditorUtilityLibrary.h"
#include "Factories/FbxAssetImportData.h"
#include "Engine/SkeletalMesh.h"
#include "EditorAssetLibrary.h"
#include "EditorReimportHandler.h"
#include "QPUtil.h"

//void UQPEUW_ResetImportScale::QP_ResetScaleAndReImport(float scale)
//{
//	TArray<UObject*> qp_objs = UEditorUtilityLibrary::GetSelectedAssets();
//	
//	for (UObject* o : qp_objs)
//	{
//
//		if (USkeletalMesh* s = Cast<USkeletalMesh>(o)) {
//			QP_ChangeScale(Cast<UFbxAssetImportData>(s->GetAssetImportData()), scale);
//		}
//		else {
//			FObjectProperty* Property = CastField<FObjectProperty>(o->GetClass()->FindPropertyByName("AssetImportData"));
//			//QP_ChangeScale(Cast<UFbxAssetImportData>(Property->ContainerPtrToValuePtr<UAssetImportData>(o)), scale);
//
//			if (Property) {
//				UFbxAssetImportData* ass = Cast<UFbxAssetImportData>(Property->GetObjectPropertyValue_InContainer(o));
//				if (ass) {
//					QP_ChangeScale(ass, scale);
//				}
//				else {
//					//UQPUtil::QP_LOG();
//					UQPUtil::QP_LOG(o->GetName() + " do not have UFbxAssetImportData");
//
//				}
//				//QP_ChangeScale(Cast<UFbxAssetImportData>(Property->ContainerPtrToValuePtr<UAssetImportData>(o)), scale);
//			}
//			else {
//				UQPUtil::QP_LOG(o->GetName()+" do not have AssetImportData");
//			}
//			
//
//		}
//		
//	}
//	FReimportManager::Instance()->ReimportMultiple(qp_objs);
//	UEditorAssetLibrary::SaveLoadedAssets(qp_objs, false);
//}
//
//void UQPEUW_ResetImportScale::QP_ChangeScale(UFbxAssetImportData* AssetImportData, float scale)
//{
//	AssetImportData->ImportUniformScale = scale;
//}
