// QIPAWORLD


#include "Animation/QPC_Scale.h"

//
//// Sets default values for this component's properties
//UQPC_Scale::UQPC_Scale()
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
//void UQPC_Scale::BeginPlay()
//{
//	Super::BeginPlay();
//	qp_rotator = GetOwner()->GetActorRotation();
//	// ...
//
//}
//
//
//// Called every frame
//void UQPC_Scale::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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


void UQPC_Scale::QP_TickAnim() {
	
	qp_owner->SetActorRelativeScale3D(qp_owner->GetActorRelativeScale3D()+FVector(qp_xSpeed * qp_tickTime, qp_ySpeed * qp_tickTime, qp_zSpeed * qp_tickTime));
	//qp_owner->AddActorLocalRotation(FRotator(-qp_ySpeed * qp_tickTime, qp_zSpeed * qp_tickTime, qp_xSpeed * qp_tickTime));
	//qp_owner->SetActorLocation(qp_owner->GetActorLocation() + qp_owner->GetActorForwardVector() * FVector());

}