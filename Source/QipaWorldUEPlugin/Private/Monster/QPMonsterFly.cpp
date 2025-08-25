// QIPAWORLD


#include "Monster/QPMonsterFly.h"

AQPMonsterFly::AQPMonsterFly(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	//qp_movementMode = MOVE_Flying;
	//qp_unchangeMovementMode = true;
}

// Called when the game starts or when spawned
void AQPMonsterFly::BeginPlay()
{
	Super::BeginPlay();
	//qp_lastRotator = GetActorRotation();
	qp_movementC->MaxFlySpeed = qp_walkSpeed;
	qp_movementC->SetMovementMode(MOVE_Flying);
}
