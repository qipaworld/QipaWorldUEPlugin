// QIPAWORLD


#include "Skill/QPS_Movement.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AQPS_Movement::AQPS_Movement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	qp_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("qp_staticMesh");
	qp_staticMesh->SetupAttachment(RootComponent);
	qp_staticMesh->SetCollisionProfileName("SkillMovement");

	qp_movement = CreateDefaultSubobject<UProjectileMovementComponent>("qp_movement");

}

// Called when the game starts or when spawned
void AQPS_Movement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQPS_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}