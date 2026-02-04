// QIPAWORLD


#include "Actor/QPActor.h"
#include "Actor/QP_AutoSpawn.h"
// Sets default values
AQPActor::AQPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	qp_root = CreateDefaultSubobject<USceneComponent>("qp_root");
	RootComponent = qp_root;
}

// Called when the game starts or when spawned
void AQPActor::BeginPlay()
{
	Super::BeginPlay();
	if (qp_autoDestroy!=0) {
		//SetLifeSpan(qp_autoDestroy);
		SetLifeSpan(qp_autoDestroy);
	}
}

void AQPActor::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	
	Super::EndPlay(EndPlayReason);
	if (qp_spawnActor) {
		qp_spawnActor->qp_actorNum--;
	}
}
//void AQPActor::QP_End() {
	/*if (qp_isAutoDestroy) {
		Destroy();
	}
	qp_isAutoDestroy = false;*/
//}
// Called every frame
void AQPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (qp_isAutoDestroy) {
		qp_autoDestroy -= DeltaTime;
		if (qp_autoDestroy <= 0) {
			QP_End();
		}
	}*/
}

