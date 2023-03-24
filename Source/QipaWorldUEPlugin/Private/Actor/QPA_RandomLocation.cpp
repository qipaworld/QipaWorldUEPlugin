// QIPAWORLD


#include "Actor/QPA_RandomLocation.h"

AQPA_RandomLocation::AQPA_RandomLocation() {
	qp_randmoLocatin = CreateDefaultSubobject<UQPRandomLocationC>("QP_RandomLocation");
	//qp_randmoLocatin->setupatt
}

void AQPA_RandomLocation::QP_RandomLocation(FVector v) {
	SetActorLocation( qp_randmoLocatin->QP_RandomLocation(qp_radius, v, qp_altitudeMin, qp_altitudeMax));
}

