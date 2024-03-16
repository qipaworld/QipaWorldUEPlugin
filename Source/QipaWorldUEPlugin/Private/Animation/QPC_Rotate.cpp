// QIPAWORLD


#include "Animation/QPC_Rotate.h"

//
//// Sets default values for this component's properties
//UQPC_Rotate::UQPC_Rotate()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UQPC_Rotate::BeginPlay()
//{
//	Super::BeginPlay();
//	qp_rotator = GetOwner()->GetActorRotation();
//	// ...
//
//}
//
//
//// Called every frame
//void UQPC_Rotate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	if (qp_sleepTime >= 0) {
//		qp_sleepTime -= DeltaTime;
//		return;
//	}
//	qp_rotator+= qp_rotatorSpeed* DeltaTime;
//	FVector v;
//	//v.Yaw += 5;
//	//GetOwner()->add;
//	// ...
//}


void UQPC_Rotate::QP_TickAnim() {

	qp_owner->AddActorLocalRotation(FRotator(-qp_ySpeed * qp_tickTime, qp_zSpeed * qp_tickTime, qp_xSpeed * qp_tickTime));
	//qp_owner->SetActorLocation(qp_owner->GetActorLocation() + qp_owner->GetActorForwardVector() * FVector());

}