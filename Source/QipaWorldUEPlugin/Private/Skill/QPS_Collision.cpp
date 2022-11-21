// QIPAWORLD


#include "Skill/QPS_Collision.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AQPS_Collision::AQPS_Collision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	qp_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("qp_staticMesh");
	//qp_staticMesh->SetupAttachment(RootComponent);
	qp_effect->SetupAttachment(qp_staticMesh);

	RootComponent = qp_staticMesh;

	qp_staticMesh->SetCollisionProfileName("SkillMovement");

}

// Called when the game starts or when spawned
void AQPS_Collision::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQPS_Collision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}