// QIPAWORLD


#include "Component/QPSC_RandomLocation.h"


UQPSC_RandomLocation::UQPSC_RandomLocation() {
	qp_randmoLocatin = CreateDefaultSubobject<UQPC_RandomLocation>("QP_RandomLocation");
	//qp_randmoLocatin->setupatt
}

void UQPSC_RandomLocation::QP_RandomLocation(FVector v) {
	SetWorldLocation(qp_randmoLocatin->QP_RandomLocation(qp_radius, v, qp_altitudeMin, qp_altitudeMax));
}
