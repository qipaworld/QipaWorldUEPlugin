// QIPAWORLD


#include "Component/QPC_RandomLocation.h"
#include "NavigationSystem.h"

FVector UQPC_RandomLocation::QP_RandomLocation(float radius, FVector target, float altitudeMin, float altitudeMax) {
	FVector RandomPoint(target);

	if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this,target, RandomPoint, radius)) {
		float z = FMath::RandRange(altitudeMin, altitudeMax);
		//GetOwner()->SetActorLocation();

		return FVector(RandomPoint.X, RandomPoint.Y, RandomPoint.Z + z);
	}
	return target;
	
}

FVector UQPC_RandomLocation::QP_RandomLocationBase(float radius) {
	return QP_RandomLocation(radius, GetOwner()->GetActorLocation());
}