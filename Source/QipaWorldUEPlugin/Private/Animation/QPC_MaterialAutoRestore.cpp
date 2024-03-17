// QIPAWORLD
#include "Animation/QPC_MaterialAutoRestore.h"

#include "GameFramework/Character.h"

//#include "Character/QPCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
UQPC_MaterialAutoRestore::UQPC_MaterialAutoRestore() {
	PrimaryComponentTick.bCanEverTick = true;

}
//void UQPC_MaterialAutoRestore::QP_SetRestoreNiagara(class UNiagaraComponent* ng) {
//	qp_restoreNg = ng;
//}
void UQPC_MaterialAutoRestore::BeginPlay() {
	Super::BeginPlay();
	
	this->SetComponentTickEnabled(true);
	if (!qp_mesh) {

		return;
	}
	for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
	{
		qp_materialDissolves.Add(qp_mesh->CreateDynamicMaterialInstance(i, qp_mesh->GetMaterial(i)));
	}
	
	qp_restoreNg = UNiagaraFunctionLibrary::SpawnSystemAttached(qp_restoreNgClass, GetOwner()->GetRootComponent(), FName("qp_dashN"), GetOwner()->GetActorLocation(), FRotator::ZeroRotator, EAttachLocation::Type::KeepWorldPosition, false);
	//
	if (qp_restoreNg) {
		qp_restoreNg->Deactivate();
	}

}

void UQPC_MaterialAutoRestore::TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	if (qp_matAmount < 1) {
		if (!qp_isDissolveMat) {
			qp_isDissolveMat = true;
			for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
			{
				qp_mesh->SetMaterial(i, qp_materialDissolves[i]);
			}
		}
		if (!qp_isRestoreNg && qp_matAmount < qp_restoreNgMin) {
			qp_isRestoreNg = true;
			if (qp_restoreNg) {
				qp_restoreNg->Activate();
			}
		}
		if (qp_isRestoreNg && qp_matAmount > qp_restoreNgMin) {
			if (qp_restoreNg) {
				qp_restoreNg->Deactivate();
			}
			qp_isRestoreNg = false;
		}
		if (qp_matAmount >= 1) {
			qp_matAmount = 1;
		}
		for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
		{
			qp_materialDissolves[i]->SetScalarParameterValue(qp_amountName, qp_matAmount);
		}
		if (qp_isRestore) {
			qp_matAmount += (qp_matAmountSpeed * DeltaTime);
		}
	}
	if (qp_isDissolveMat && qp_matAmount >= 1) {
		if (qp_materials.Num() > 0) {
			qp_isDissolveMat = false;
			for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
			{
				qp_mesh->SetMaterial(i, qp_materials[i]);
			}
		}
		
	}

}
void UQPC_MaterialAutoRestore::QP_SetMatAmount(float amount) {
	if (amount > 0) {
	qp_matAmount = amount;
	}

}
