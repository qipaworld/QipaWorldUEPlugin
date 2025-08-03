// QIPAWORLD


#include "Actor/QPA_DestructibleStar.h"

AQPA_DestructibleStar::AQPA_DestructibleStar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//RootComponent = qp_geometryCollection;
	qp_fadeMaterials = CreateDefaultSubobject<UQPC_FadeMaterials>(TEXT("qp_fadeMaterials"));

	

	//UE_LOG(LogTemp, Warning, TEXT("___!______%d"), qp_fadeMaterials->qp_materials.Num());
	qp_fadeMaterials->qp_mesh = qp_geometryCollection;
	//qp_fadeMaterial->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AQPA_DestructibleStar::BeginPlay()
{
	Super::BeginPlay();

	/*for (int32 i = 0; i < qp_geometryCollection->GetNumMaterials(); ++i)
	{
		qp_fadeMaterials->qp_materials.Add(qp_geometryCollection->CreateDynamicMaterialInstance(i, qp_geometryCollection->GetMaterial(i)));
		qp_fadeMaterials->qp_fadeValues.Add(0);
		qp_fadeMaterials->qp_fadeSpeeds.Add(0);
		

	}*/
	if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(false);
		//qp_fadeMaterials->SetComponentTickEnabled(false);

	}
	//qp_geometryCollection->SetEnableGravity(false);
	//qp_geometryCollection->MarkRenderStateDirty();
	
	//qp_geometryCollection->ForceRecreateRenderState_Concurrent();
}
void AQPA_DestructibleStar::QP_OnTriggerSimulatePhysicsBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	//QP_End();
	//if ("BP_ChaosJar_116" == GetActorLabel())
		//UE_LOG(LogTemp, Warning, TEXT("___!aa___d___%s"), *GetActorLabel());
	Super::QP_OnTriggerSimulatePhysicsBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	/*if (qp_autoSimulatePhysics) {
		qp_geometryCollection->SetSimulatePhysics(true);
		qp_geometryCollection->SetEnableGravity(true);
	}*/
	if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(true);
		//qp_fadeMaterials->SetComponentTickEnabled(true);
	}
}

void AQPA_DestructibleStar::QP_OnTriggerSimulatePhysicsEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("___!asda___d___%s"), *GetActorLabel());
	Super::QP_OnTriggerSimulatePhysicsEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if (qp_autoSimulatePhysics) {
		//SetActorTickEnabled(false);
		/*qp_fadeMaterials->SetComponentTickEnabled(false);
		if (qp_isAutoDestroy) {
			QP_End();
		}*/
	}
	
}
void AQPA_DestructibleStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (qp_delayTime >= 0) {
		qp_delayTime -= DeltaTime;
	}
	else {*/
		if (qp_fadeMaterials->qp_showType == EQPFadeType::SHOW) {
			qp_showedTime -= DeltaTime;
			if (qp_showedTime <= 0) {
				qp_fadeMaterials->QP_FadeOut(qp_fadeOutTime);
				//qp_isShow = false;

			}
		}
		
	//}
	
}
//void AQPA_DestructibleStar::QP_OnBroken(const FChaosBreakEvent& BreakEvent)
//{
	//Super::QP_OnBroken(BreakEvent);
	//qp_autoDestroy = qp_delayDestroy;
	//qp_isAutoDestroy = true;
//}
//void AQPA_DestructibleStar::QP_OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("___!_______%s"), *OtherActor->GetName());
//}
void AQPA_DestructibleStar::QP_OnChunkHit(const FChaosPhysicsCollisionInfo& CollisionInfo)
{
	Super::QP_OnChunkHit(CollisionInfo);
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
	/*if ("BP_ChaosJar_116" == GetActorLabel())
		UE_LOG(LogTemp, Warning, TEXT("___!___d___%s"), *GetActorLabel());*/
	if ((CollisionInfo.Velocity.Size() + CollisionInfo.OtherVelocity.Size()) > qp_fadeInMinVelocity) {
		
		qp_showedTime = qp_showTime;
		/*if (qp_fadeMaterials->qp_showType == EQPFadeType::SHOW || qp_fadeMaterials->qp_showType == EQPFadeType::FADE_IN) {
			return;
		}*/
		qp_isMove = true;

		qp_fadeMaterials->QP_FadeIn(qp_fadeInTime);
		//qp_isShow = true;
		/*if("BP_ChaosJar_116" == GetActorLabel())
		UE_LOG(LogTemp, Warning, TEXT("___!______%s"),*GetActorLabel());*/

		//qp_autoDestroy = qp_delayDestroy;
		//qp_playRandomSound->QP_SetVolume(velocity / qp_maxSpeed * (1 - qp_minVolume) + qp_minVolume);
		//qp_playRandomSound->QP_Play(CollisionInfo.OtherComponent->GetOwner());

	}
}