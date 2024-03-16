// QIPAWORLD


#include "Animation/QPC_AnimBase.h"


// Sets default values for this component's properties
UQPC_AnimBase::UQPC_AnimBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UQPC_AnimBase::BeginPlay()
{
	Super::BeginPlay();
	qp_owner = GetOwner();
	if (!qp_autoPlay) {
		SetComponentTickEnabled(false);
	}
	//qp_rotator = GetOwner()->GetActorRotation();
	// ...

}


// Called every frame
void UQPC_AnimBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	qp_tickTime = DeltaTime;
	QP_TickAnim();
}
void UQPC_AnimBase::QP_Play() {
	SetComponentTickEnabled(true);
}
void UQPC_AnimBase::QP_Stop() {
	SetComponentTickEnabled(false);
}
