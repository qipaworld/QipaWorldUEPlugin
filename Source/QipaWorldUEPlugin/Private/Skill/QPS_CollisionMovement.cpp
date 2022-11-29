// QIPAWORLD


#include "Skill/QPS_CollisionMovement.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AQPS_CollisionMovement::AQPS_CollisionMovement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//qp_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("qp_staticMesh");
	//qp_staticMesh->SetupAttachment(RootComponent);
	//qp_effect->SetupAttachment(qp_staticMesh);

	//RootComponent = qp_staticMesh;

	//qp_staticMesh->SetCollisionProfileName("SkillMovement");
	qp_movement = CreateDefaultSubobject<UProjectileMovementComponent>("qp_movement");

}

// Called when the game starts or when spawned
void AQPS_CollisionMovement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQPS_CollisionMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}