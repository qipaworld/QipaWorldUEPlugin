// QIPAWORLD
#include "Animation/QPC_MaterialDissolve.h"

#include "GameFramework/Character.h"

//#include "Character/QPCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
UQPC_MaterialDissolve::UQPC_MaterialDissolve() {
	PrimaryComponentTick.bCanEverTick = true;
}
//void UQPC_MaterialDissolve::QP_SetRestoreNiagara(class UNiagaraComponent* ng) {
//	qp_restoreNg = ng;
//}
void UQPC_MaterialDissolve::BeginPlay() {
	Super::BeginPlay();
	
	this->SetComponentTickEnabled(true);
	if (!qp_mesh) {

		return;
	}
	for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
	{
		qp_materialDissolves.Add(qp_mesh->CreateDynamicMaterialInstance(i, qp_mesh->GetMaterial(i)));
		//qp_materialDissolves[i]->SetScalarParameterValue(qp_amountName, qp_matAmount);

	}
	
	qp_restoreNg = UNiagaraFunctionLibrary::SpawnSystemAttached(qp_restoreNgClass, GetOwner()->GetRootComponent(), FName("qp_dashN"), GetOwner()->GetActorLocation(), FRotator::ZeroRotator, EAttachLocation::Type::KeepWorldPosition, false);
	//
	if (qp_restoreNg) {
		qp_restoreNg->Deactivate();
	}
	if (qp_materials.Num() > 0) {
		for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
		{
			qp_mesh->SetMaterial(i, qp_materials[i]);
		}
	}

}

void UQPC_MaterialDissolve::TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	if (isDissolve) {
		
		qp_matAmount -= (qp_matAmountSpeed * DeltaTime);
		if (qp_matAmount <= 0) {
			qp_matAmount = 0;
		}
		for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
		{
			qp_materialDissolves[i]->SetScalarParameterValue(qp_amountName, qp_matAmount);
		}
		if (qp_matAmount == 0) {
			QP_Stop();
		}
		
	
	}

}
void UQPC_MaterialDissolve::QP_SetMatAmount(float amount) {
	if (amount > 1)qp_matAmount = 1;
	else if (amount < 0)qp_matAmount = 0;
	else qp_matAmount = amount;
}
void UQPC_MaterialDissolve::QP_Play() {
	isDissolve = true;
	for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
	{
		qp_mesh->SetMaterial(i, qp_materialDissolves[i]);
	}
	if (qp_restoreNg) {
		qp_restoreNg->Activate();
	}
}
void UQPC_MaterialDissolve::QP_Stop() {
	isDissolve = false;
	if (qp_restoreNg) {
		qp_restoreNg->Deactivate();
	}
	if (qp_materials.Num() > 0) {
		for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
		{
			qp_mesh->SetMaterial(i, qp_materials[i]);
		}
	}
}