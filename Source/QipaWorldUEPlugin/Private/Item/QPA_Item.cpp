// QIPAWORLD


#include "Item/QPA_Item.h"
#include "Item/QPGIM_Item.h"

TMap<FName, TMap<FName, float>> AQPA_Item::qp_allItemTypes = TMap<FName, TMap<FName, float>>();

AQPA_Item::AQPA_Item()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//RootComponent = qp_geometryCollection;
	//qp_fadeMaterials = CreateDefaultSubobject<UQPC_FadeMaterials>(TEXT("qp_fadeMaterials"));
	qp_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("qp_mesh"));
	qp_sphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("qp_sphereTrigger"));
	qp_sphereTrigger->SetupAttachment(RootComponent);


	//UE_LOG(LogTemp, Warning, TEXT("___!______%d"), qp_fadeMaterials->qp_materials.Num());
	//qp_fadeMaterials->qp_mesh = qp_mesh;
	qp_mesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AQPA_Item::BeginPlay()
{
	Super::BeginPlay();

	
	UMaterialInstanceDynamic* d;
	for (int32 i = 0; i < qp_mesh->GetNumMaterials(); ++i)
	{
		d = qp_mesh->CreateDynamicMaterialInstance(i, qp_mesh->GetMaterial(i));
		d->SetScalarParameterValue("qp_emissive", 0);
		d->SetTextureParameterValue("qp_texture", qp_texture);
		d->SetVectorParameterValue("qp_color", qp_color);
		qp_materials.Add(d);
	}
	//qp_mesh->OnComponentHit.AddDynamic(this, &AQPA_Item::QP_OnHit);
	qp_sphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AQPA_Item::QP_OnTriggerOverlapBegin);
	qp_sphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AQPA_Item::QP_OnTriggerOverlapEnd);
	//if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(false);
		//qp_fadeMaterials->SetComponentTickEnabled(false);
//
	//}
	//qp_geometryCollection->SetEnableGravity(false);
	//qp_geometryCollection->MarkRenderStateDirty();
	
	//qp_geometryCollection->ForceRecreateRenderState_Concurrent();
}
void AQPA_Item::QP_MakeItemData() {
	if (!qp_allItemTypes.Contains(qp_itemName)) {

		UQPDA_Item* itemD = UQPGIM_Item::qp_staticObject->QP_GetItemData(qp_itemName);
		TMap<FName, float> t;
		for (TFieldIterator<FProperty> It(itemD->GetClass()); It; ++It)
		{
			FProperty* AttrProp = *It;

			
			if (!AttrProp->IsA<FFloatProperty>()) continue;

			FFloatProperty* Obj = CastField<FFloatProperty>(AttrProp);

			//UE_LOG(LogTemp, Warning, TEXT("___!____%s__))))))))"), *AttrProp->GetFName().ToString());
			t.Add(AttrProp->GetFName(), Obj->GetPropertyValue_InContainer(itemD));

		}
		qp_allItemTypes.Add(qp_itemName, t);
	}
	qp_itemData.qp_itemName = qp_itemName;
	qp_itemData.qp_createTime = FDateTime::UtcNow().ToUnixTimestamp() ;
	//fl ; 
	TMap<FName, float>& t = qp_allItemTypes[qp_itemName];
	float r = 0;
	if (t.Contains("qp_range")) {
		r = t["qp_range"];
	}
	float sX = qp_mesh->GetRelativeScale3D().X;
	sX = sX + sX * FMath::FRandRange(0.f, 1.f);
	qp_mesh->SetRelativeScale3D(FVector(sX,sX,sX));
	for (auto v : t) {
		//UE_LOG(LogTemp, Warning, TEXT("___!____%s__))))))))"), *AttrProp->GetFName().ToString());

		qp_itemData.qp_datas.Add(v.Key, v.Value + v.Value * r * FMath::FRandRange(0.f, 1.f));
	}
	if (t.Contains("qp_range")) {
		//r = t["qp_range"];
		qp_itemData.qp_datas["qp_range"] = r;
	}
}
void AQPA_Item::QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!______))))))))"));
	qp_autoEmissive = 1;
	qp_isShow = true;
	
}

void AQPA_Item::QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!_sdfsd_____))))))))"));
	qp_isShow = false;
	qp_autoEmissive = -1;


	/*for (auto v : qp_materials)
	{

		v->SetScalarParameterValue("qp_emissive", 0);
	}*/
	
}
void AQPA_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (qp_isShow) {
		if (qp_emissive > qp_emissiveMax) {
			qp_autoEmissive =  -1;
		}
		else if (qp_emissive < qp_emissiveMin) {
			qp_autoEmissive = 1;

		}
	}
	if (qp_isShow || qp_emissive > qp_emissiveMin) {

		qp_emissive += (qp_speed * DeltaTime* qp_autoEmissive);
		for (auto v : qp_materials)
		{

			v->SetScalarParameterValue("qp_emissive", qp_emissive);
		}
	}
	/*if(qp_emissive> qp_emissiveMin)
	{
		for (auto v : qp_materials)
		{

			v->SetScalarParameterValue("qp_emissive", qp_emissive);
		}
	}*/
	/*if (qp_delayTime >= 0) {
		qp_delayTime -= DeltaTime;
	}
	else {*/
		//if (qp_fadeMaterials->qp_showType == EQPFadeType::SHOW) {
		//	qp_showedTime -= DeltaTime;
		//	if (qp_showedTime <= 0) {
		//		qp_fadeMaterials->QP_FadeOut(qp_fadeOutTime);
		//		//qp_isShow = false;

		//	}
		//}
		
	//}
	
}
////void AQPA_Item::QP_OnBroken(const FChaosBreakEvent& BreakEvent)
////{
//	//Super::QP_OnBroken(BreakEvent);
//	//qp_autoDestroy = qp_delayDestroy;
//	//qp_isAutoDestroy = true;
////}
////void AQPA_Item::QP_OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
//	//UE_LOG(LogTemp, Warning, TEXT("___!_______%s"), *OtherActor->GetName());
////}
//void AQPA_Item::QP_OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	
//	//UE_LOG(LogTemp, Warning, TEXT("___!______%d"), qp_geometryCollection->GetNumMaterials());
//	//FVector Location = CollisionInfo.ContactLocation;
//
//	//if (CollisionInfo.AccumulatedImpulse.Size() > 10.0f)
//	//{
//		//UGameplayStatics::PlaySoundAtLocation(this, ImpactSoundCue, Location);
//	//}
//	//UE_LOG(LogTemp, Warning, TEXT("___2_"));
//	//float velocity = ;
//	//UE_LOG(LogTemp, Warning, TEXT("___%f_"), velocity);
//	//UE_LOG(LogTemp, Warning, TEXT("___!______"));
//	/*if (qp_delayTime >= 0) {
//		return;
//	}*/
//	/*if ("BP_ChaosJar_116" == GetActorLabel())
//		UE_LOG(LogTemp, Warning, TEXT("___!___d___%s"), *GetActorLabel());*/
//	if ((NormalImpulse.Size()) > qp_fadeInMinVelocity) {
//		
//		qp_showedTime = qp_showTime;
//		/*if (qp_fadeMaterials->qp_showType == EQPFadeType::SHOW || qp_fadeMaterials->qp_showType == EQPFadeType::FADE_IN) {
//			return;
//		}*/
//
//		qp_fadeMaterials->QP_FadeIn(qp_fadeInTime);
//		//qp_isShow = true;
//		/*if("BP_ChaosJar_116" == GetActorLabel())
//		UE_LOG(LogTemp, Warning, TEXT("___!______%s"),*GetActorLabel());*/
//
//		//qp_autoDestroy = qp_delayDestroy;
//		//qp_playRandomSound->QP_SetVolume(velocity / qp_maxSpeed * (1 - qp_minVolume) + qp_minVolume);
//		//qp_playRandomSound->QP_Play(CollisionInfo.OtherComponent->GetOwner());
//
//	}
//}