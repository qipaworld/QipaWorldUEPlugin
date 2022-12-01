// QIPAWORLD


#include "Skill/QPS_Movement.h"

// Sets default values
AQPS_Movement::AQPS_Movement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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


UProjectileMovementComponent* AQPS_Movement::QP_GetMovement()
{
	return qp_movement;
}

void AQPS_Movement::SetMoveVelocityInLocalSpace(FVector NewVelocity)
{
	qp_movement->SetVelocityInLocalSpace(NewVelocity);
	//qp_movement->InitialSpeed = qp_movement->InitialSpeed + speed;
}

void AQPS_Movement::QP_SetMaxMoveSpeed(float speed)
{
	qp_movement->MaxSpeed = speed;
}

void AQPS_Movement::QP_AddMoveForce(FVector Force) {
	qp_movement->AddForce(Force);
}

//void AQPS_CollisionMovement::QP_AddLimitForce(FVector Force) {
//	
//	qp_movement->LimitVelocity(qp_movement->Velocity + Force);
//	
//	//qp_movement->SetVelocityInLocalSpace(qp_movement->Velocity+ FVector(Force.Size(), 0, 0));
//}

//void AQPS_CollisionMovement::QP_AddMoveSpeed(FVector Force) {
//	qp_movement->SetVelocityInLocalSpace(Force+FVector(qp_movement->Velocity.Size(), 0, 0));
//}
//
//void AQPS_CollisionMovement::QP_AddMoveSpeedFloat(float speed) {
//	
//	qp_movement->SetVelocityInLocalSpace(FVector(qp_movement->Velocity.Size()+ speed, 0, 0));
//}
void AQPS_Movement::QP_AddMoveVelocity(FVector NewVelocity) {
	qp_movement->Velocity = qp_movement->Velocity + NewVelocity;
}
