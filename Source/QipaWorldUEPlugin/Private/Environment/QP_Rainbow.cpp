// QIPAWORLD


#include "Environment/QP_Rainbow.h"

#include "Data/QPData.h"



AQP_Rainbow::AQP_Rainbow()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	//RootComponent = qp_geometryCollection;
	//qp_fadeMaterials = CreateDefaultSubobject<UQPC_FadeMaterials>(TEXT("qp_fadeMaterials"));
	qp_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("qp_mesh"));



	//UE_LOG(LogTemp, Warning, TEXT("___!______%d"), qp_fadeMaterials->qp_materials.Num());
	//qp_fadeMaterials->qp_mesh = qp_mesh;
	qp_mesh->SetupAttachment(RootComponent);

	

}


void AQP_Rainbow::BeginPlay()
{
	Super::BeginPlay();
	qp_parameterValueRange = qp_parameterValueMax - qp_parameterValueMin;
	qp_outRange = 1 - qp_showMax;
	if (!qp_material) {
		qp_material = qp_mesh->CreateDynamicMaterialInstance(qp_materialIndex, qp_mesh->GetMaterial(qp_materialIndex));
	}
	UQPGIM_Map::qp_staticObject->QP_GetMapData()->qp_dataDelegate.AddUObject(this, &AQP_Rainbow::QP_BindMapData);
		qp_mesh->SetActive(qp_showType == UQPGIM_Map::qp_staticObject->qp_mapSunType);
		qp_mesh->SetVisibility(qp_showType == UQPGIM_Map::qp_staticObject->qp_mapSunType);
	//if () {
	//}
}

void AQP_Rainbow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (qp_mesh->IsActive()) {
		//;
		if (qp_showMax > UQPGIM_Map::qp_staticObject->qp_mapSunTimeEx) {
			qp_material->SetScalarParameterValue(qp_parameterValueName, qp_parameterValueRange * (UQPGIM_Map::qp_staticObject->qp_mapSunTimeEx/ qp_showMax) + qp_parameterValueMin);
		}
		else {
			
			qp_material->SetScalarParameterValue(qp_parameterValueName, qp_parameterValueRange * (1 - ((UQPGIM_Map::qp_staticObject->qp_mapSunTimeEx - qp_showMax) / qp_outRange)) + qp_parameterValueMin);
		}
	}

	///*if (qp_delayTime >= 0) {
	//	qp_delayTime -= DeltaTime;
	//}
	//else {*/
	//if (qp_fadeMaterials->qp_showType == EQPFadeType::SHOW) {
	//	qp_showedTime -= DeltaTime;
	//	if (qp_showedTime <= 0) {
	//		qp_fadeMaterials->QP_FadeOut(qp_fadeOutTime);
	//		//qp_isShow = false;

	//	}
	//}

	////}

}

void AQP_Rainbow::QP_BindMapData(UQPData* data)
{

	if (data->QP_IsChange<FName, bool>("sumTypeChange", EQPDataValueType::BOOL)) {
		qp_mesh->SetActive(qp_showType == UQPGIM_Map::qp_staticObject->qp_mapSunType);
		qp_mesh->SetVisibility(qp_showType == UQPGIM_Map::qp_staticObject->qp_mapSunType);
	}

}