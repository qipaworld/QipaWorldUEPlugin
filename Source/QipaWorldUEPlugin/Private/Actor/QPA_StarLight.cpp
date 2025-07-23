// QIPAWORLD


#include "Actor/QPA_StarLight.h"

AQPA_StarLight::AQPA_StarLight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	qp_fadeLight = CreateDefaultSubobject<UQPC_FadeLight>(TEXT("qp_fadeLight"));
	qp_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("qp_mesh"));
	
	qp_mesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AQPA_StarLight::BeginPlay()
{
	Super::BeginPlay();

	qp_mesh->OnComponentHit.AddDynamic(this, &AQPA_StarLight::QP_OnHit);
	//if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(false);
		//qp_fadeLight->SetComponentTickEnabled(false);
//
	//}
	//qp_geometryCollection->SetEnableGravity(false);
	//qp_geometryCollection->MarkRenderStateDirty();

	//qp_geometryCollection->ForceRecreateRenderState_Concurrent();
}
//void AQPA_StarLight::QP_OnTriggerSimulatePhysicsBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
//	//QP_End();
//	//if ("BP_ChaosJar_116" == GetActorLabel())
//		//UE_LOG(LogTemp, Warning, TEXT("___!aa___d___%s"), *GetActorLabel());
//	Super::QP_OnTriggerSimulatePhysicsBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
//	/*if (qp_autoSimulatePhysics) {
//		qp_geometryCollection->SetSimulatePhysics(true);
//		qp_geometryCollection->SetEnableGravity(true);
//	}*/
//	if (qp_autoSimulatePhysics) {
//		//SetActorTickEnabled(true);
//		//qp_fadeLight->SetComponentTickEnabled(true);
//	}
//}
//
//void AQPA_StarLight::QP_OnTriggerSimulatePhysicsEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("___!asda___d___%s"), *GetActorLabel());
//	Super::QP_OnTriggerSimulatePhysicsEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
//	if (qp_autoSimulatePhysics) {
//		//SetActorTickEnabled(false);
//		/*qp_fadeLight->SetComponentTickEnabled(false);
//		if (qp_isAutoDestroy) {
//			QP_End();
//		}*/
//	}
//	
//}
void AQPA_StarLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (qp_delayTime >= 0) {
		qp_delayTime -= DeltaTime;
	}
	else {*/
	if (qp_fadeLight->qp_showType == EQPFadeType::SHOW) {
		qp_showedTime -= DeltaTime;
		if (qp_showedTime <= 0) {
			qp_fadeLight->QP_FadeOut(qp_fadeOutTime);
			//qp_isShow = false;

		}
	}

	//}

}
//void AQPA_StarLight::QP_OnBroken(const FChaosBreakEvent& BreakEvent)
//{
	//Super::QP_OnBroken(BreakEvent);
	//qp_autoDestroy = qp_delayDestroy;
	//qp_isAutoDestroy = true;
//}
//void AQPA_StarLight::QP_OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("___!_______%s"), *OtherActor->GetName());
//}
void AQPA_StarLight::QP_OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	//UE_LOG(LogTemp, Warning, TEXT("___!______%d"), qp_geometryCollection->GetNumMaterials());
	//FVector Location = CollisionInfo.ContactLocation;

	//if (CollisionInfo.AccumulatedImpulse.Size() > 10.0f)
	//{
		//UGameplayStatics::PlaySoundAtLocation(this, ImpactSoundCue, Location);
	//}
	//UE_LOG(LogTemp, Warning, TEXT("___2_"));
	//float velocity = ;
	//UE_LOG(LogTemp, Warning, TEXT("___%f_"), velocity);
	//UE_LOG(LogTemp, Warning, TEXT("___!______"));
	/*if (qp_delayTime >= 0) {
		return;
	}*/
	/*if ("BP_ChaosJar_116" == GetActorLabel())*/
		//UE_LOG(LogTemp, Warning, TEXT("___!___d___%f"), NormalImpulse.Size());
	if ((NormalImpulse.Size()) > qp_fadeInMinVelocity) {

		qp_showedTime = qp_showTime;
		/*if (qp_fadeLight->qp_showType == EQPFadeType::SHOW || qp_fadeLight->qp_showType == EQPFadeType::FADE_IN) {
			return;
		}*/

		qp_fadeLight->QP_FadeIn(qp_fadeInTime);
		//qp_isShow = true;
		/*if("BP_ChaosJar_116" == GetActorLabel())
		UE_LOG(LogTemp, Warning, TEXT("___!______%s"),*GetActorLabel());*/

		//qp_autoDestroy = qp_delayDestroy;
		//qp_playRandomSound->QP_SetVolume(velocity / qp_maxSpeed * (1 - qp_minVolume) + qp_minVolume);
		//qp_playRandomSound->QP_Play(CollisionInfo.OtherComponent->GetOwner());

	}
}

void AQPA_StarLight::QP_FadeIn(float qp_maxTime_) {
	qp_showedTime = qp_maxTime_;

	qp_fadeLight->QP_FadeIn(qp_fadeInTime);
}

void AQPA_StarLight::QP_FadeOut() {
	qp_showedTime = 0;
	//qp_fadeLight->QP_FadeOut(qp_fadeOutTime);
}
