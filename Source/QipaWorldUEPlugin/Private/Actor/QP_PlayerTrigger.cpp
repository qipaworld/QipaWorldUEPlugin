// QIPAWORLD


#include "Actor/QP_PlayerTrigger.h"




AQP_PlayerTrigger::AQP_PlayerTrigger() {
	qp_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("qp_triggerBox"));
	qp_triggerBox->SetupAttachment(RootComponent);

	// 正方形尺寸（XYZ，自行改）
	qp_triggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	// 只做触发
	qp_triggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
	qp_triggerBox->SetGenerateOverlapEvents(true);

	qp_triggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	qp_triggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//UCollisionProfile* Profile = UCollisionProfile::Get();
	//EObjectTypeQuery::ObjectTypeQuery1
	//const int32 Index = Profile->GetChannelIndexFromName(TEXT("Player"));
	//Profile->channe
	//UEngineTypes::ConvertToCollisionChannel(EObjectTypeQuery::ObjectTypeQuery1);
	ECollisionChannel PlayerChannel =
		UCollisionProfile::Get()->ConvertToCollisionChannel(false,6);
	qp_triggerBox->SetCollisionResponseToChannel(PlayerChannel, ECR_Overlap);
}

void AQP_PlayerTrigger::BeginPlay()
{
	Super::BeginPlay();


	/*UMaterialInstanceDynamic* d;
	for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
	{
		d = qp_mesh->CreateDynamicMaterialInstance(i, qp_mesh->GetMaterial(i));
		d->SetScalarParameterValue("qp_emissive", 0);
		d->SetTextureParameterValue("qp_texture", qp_texture);
		d->SetVectorParameterValue("qp_color", qp_color);
		qp_materials.Add(d);
	}*/
	//qp_mesh->OnComponentHit.AddDynamic(this, &AQPA_Item::QP_OnHit);
	qp_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AQP_PlayerTrigger::QP_OnTriggerOverlapBegin);
	qp_triggerBox->OnComponentEndOverlap.AddDynamic(this, &AQP_PlayerTrigger::QP_OnTriggerOverlapEnd);
	//if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(false);
		//qp_fadeMaterials->SetComponentTickEnabled(false);
//
	//}
	//qp_geometryCollection->SetEnableGravity(false);
	//qp_geometryCollection->MarkRenderStateDirty();

	//qp_geometryCollection->ForceRecreateRenderState_Concurrent();
}


void AQP_PlayerTrigger::QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!______))))))))"));
	//qp_autoEmissive = 1;
	//qp_isShow = true;

}

void AQP_PlayerTrigger::QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!_sdfsd_____))))))))"));
	//qp_isShow = false;
	//qp_autoEmissive = -1;


	/*for (auto v : qp_materials)
	{

		v->SetScalarParameterValue("qp_emissive", 0);
	}*/

}