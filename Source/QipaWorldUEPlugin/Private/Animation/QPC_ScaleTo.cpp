// QIPAWORLD


#include "Animation/QPC_ScaleTo.h"


// Sets default values for this component's properties
//UQPC_ScaleTo::UQPC_ScaleTo()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}


// Called when the game starts
void UQPC_ScaleTo::BeginPlay()
{
	Super::BeginPlay();
	//FRotator r = qp_owner->GetRootComponent()->GetRelativeRotation();
	//float r_r = r.Roll < 0 ? r.Roll + 360 : r.Roll;
	//float r_y = r.Yaw < 0 ? r.Yaw + 360 : r.Yaw;
	//float r_p = r.Pitch < 0 ? r.Pitch + 360 : r.Pitch;
	
	qp_xSpeed = qp_targetScale.X / qp_time;
	qp_zSpeed = qp_targetScale.Z / qp_time;
	qp_ySpeed = qp_targetScale.Y / qp_time;
}
void UQPC_ScaleTo::QP_SetScaleTarget(const FVector& v) {
	qp_xSpeed = v.X / qp_time;
	qp_zSpeed = v.Z / qp_time;
	qp_ySpeed = v.Y / qp_time;
}

// Called every frame
//void UQPC_ScaleTo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	if (qp_sleepTime >= 0) {
//		qp_sleepTime -= DeltaTime;
//		return;
//	}
//	if (qp_time >= 0) {
//
//		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//		qp_time -= DeltaTime;
//	}
//	
//}

void UQPC_ScaleTo::QP_TickAnim() {

	//qp_owner->AddActorLocalRotation(FRotator(qp_ySpeed * qp_tickTime, qp_zSpeed * qp_tickTime, qp_xSpeed * qp_tickTime));
		if (qp_time >= 0) {

		Super::QP_TickAnim();
		qp_time -= qp_tickTime;
		}
		else {
			QP_Stop();
		}
	//qp_owner->SetActorLocation(qp_owner->GetActorLocation() + qp_owner->GetActorForwardVector() * FVector());

}