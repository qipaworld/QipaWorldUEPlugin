// QIPAWORLD


#include "Animation/QPC_Move.h"

// Sets default values for this component's properties
//UQPC_Move::UQPC_Move()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	//PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}


// Called when the game starts
//void UQPC_Move::BeginPlay()
//{
	//Super::BeginPlay();
	
	//qp_vector = qp_owner->GetActorLocation();
	 //;
	//UE_LOG(LogTemp, Log, TEXT("__component__%s"), *(qp_vector.ToString()));

	// ...
	
//}


// Called every frame
//void UQPC_Move::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	if (qp_sleepTime >= 0) {
//		qp_sleepTime -= DeltaTime;
//		return;
//	}
//	qp_vector += qp_vectorSpeed * DeltaTime;
//	GetOwner()->SetActorRelativeLocation(qp_vector);
//	//GetOwner()->GetTransform()
//	// ...
//}

void UQPC_Move::QP_TickAnim() {
	
	//FVector v= qp_owner->GetActorForwardVector() ;
	//FRotationMatrix RotationMatrix(v.Rotation());
	//FVector RotatedVector = RotationMatrix.TransformVector(qp_vectorSpeed * qp_tickTime);
	qp_owner->AddActorLocalOffset(FVector(qp_xSpeed * qp_tickTime, qp_ySpeed * qp_tickTime, qp_zSpeed * qp_tickTime));//->AddRelativeLocation(RotatedVector);
	//qp_owner->GetRootComponent()->SetRelativeLocation_Direct(qp_owner->GetRootComponent()->GetRelativeLocation()+ qp_vectorSpeed * qp_tickTime);;
	//qp_vector += (v * qp_vectorSpeed * qp_tickTime);
	//qp_owner->SetActorLocation(qp_vector);
	
}
//void UQPC_Move::QP_Play() {
	//qp_vector = qp_owner->GetActorLocation();
	//Super::QP_Play();
//}
//void UQPC_Move::QP_Stop() {
	//Super::QP_Stop();

//}