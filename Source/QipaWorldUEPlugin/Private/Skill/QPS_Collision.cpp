// QIPAWORLD


#include "Skill/QPS_Collision.h"
#include "Particles/ParticleSystemComponent.h"
#include "QPUtil.h"

// Sets default values
AQPS_Collision::AQPS_Collision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	qp_sphere = CreateDefaultSubobject<USphereComponent>("qp_sphere");
	//qp_staticMesh->SetupAttachment(RootComponent);
	qp_skillNiagara->SetupAttachment(qp_sphere);

	RootComponent = qp_sphere;

	qp_sphere->SetCollisionProfileName("SkillMovement");

	// ÉèÖÃÅö×²ÏìÓ¦ÉèÖÃ
	//Cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// °ó¶¨º¯Êý
	

	// °ó¶¨º¯Êý Ê¹ÓÃÎ¯ÍÐ
	//FScriptDelegate OverlapEndDelegate;
	//OverlapEndDelegate.BindUFunction(this, TEXT("OnOverlapEnd"));
	//qp_sphere->OnComponentBeginOverlap.Add(OverlapEndDelegate);

	// °ó¶¨Åö×²º¯Êý
	

	qp_bustNiagara = CreateDefaultSubobject<UNiagaraComponent>("qp_bustNiagara");
	qp_bustNiagara->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQPS_Collision::BeginPlay()
{
	Super::BeginPlay();
	qp_sphere->OnComponentBeginOverlap.AddDynamic(this, &AQPS_Collision::QP_OnSkillOverlapBegin);
	qp_sphere->OnComponentEndOverlap.AddDynamic(this, &AQPS_Collision::QP_OnSkillOverlapEnd);
	qp_sphere->OnComponentHit.AddDynamic(this, &AQPS_Collision::QP_OnSkillHit);
	qp_bustNiagara->Deactivate();
}

// Called every frame
void AQPS_Collision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AQPS_Collision::QP_OnSkillOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	QP_End();

}

void AQPS_Collision::QP_OnSkillOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UQPUtil::QP_LOG("Overlap End");
}

void AQPS_Collision::QP_OnSkillHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UQPUtil::QP_LOG("Hit");
	//Destroy();
}
void AQPS_Collision::QP_End() {
	qp_bustNiagara->Activate();
	qp_skillNiagara->DestroyInstance();
	SetLifeSpan(qp_bustDestroy);
	qp_isAutoDestroy = false;
}