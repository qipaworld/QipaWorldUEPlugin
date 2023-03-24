// QIPAWORLD


#include "Component/QPRandomLocationC.h"
#include "NavigationSystem.h"

FVector UQPRandomLocationC::QP_RandomLocation(float radius, FVector target, float altitudeMin, float altitudeMax) {
	FVector RandomPoint(target);

	if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this,target, RandomPoint, radius)) {
		float z = FMath::RandRange(altitudeMin, altitudeMax);
		//GetOwner()->SetActorLocation();

		return FVector(RandomPoint.X, RandomPoint.Y, RandomPoint.Z + z);
	}
	return target;
	
}

FVector UQPRandomLocationC::QP_RandomLocationBase(float radius) {
	return QP_RandomLocation(radius, GetOwner()->GetActorLocation());
}