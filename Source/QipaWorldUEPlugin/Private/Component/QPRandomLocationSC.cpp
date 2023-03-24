// QIPAWORLD


#include "Component/QPRandomLocationSC.h"


UQPRandomLocationSC::UQPRandomLocationSC() {
	qp_randmoLocatin = CreateDefaultSubobject<UQPRandomLocationC>("QP_RandomLocation");
	//qp_randmoLocatin->setupatt
}

void UQPRandomLocationSC::QP_RandomLocation(FVector v) {
	SetWorldLocation(qp_randmoLocatin->QP_RandomLocation(qp_radius, v, qp_altitudeMin, qp_altitudeMax));
}
