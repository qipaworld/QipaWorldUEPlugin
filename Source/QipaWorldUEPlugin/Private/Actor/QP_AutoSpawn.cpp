// QIPAWORLD


#include "Actor/QP_AutoSpawn.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"

 AQP_AutoSpawn::AQP_AutoSpawn() {
#if WITH_EDITOR
	qp_showSphere = CreateDefaultSubobject<USphereComponent>(TEXT("qp_showSphere"));
	qp_showSphere->InitSphereRadius(qp_radius);
	qp_showSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	qp_showSphere->SetHiddenInGame(true);      // 运行时隐藏
	qp_showSphere->bDrawOnlyIfSelected = true;
	qp_showSphere->SetupAttachment(RootComponent);

	qp_billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("qp_billboard"));
	qp_billboard->SetupAttachment(RootComponent);
	qp_billboard->bIsScreenSizeScaled = true;

#endif
}
void AQP_AutoSpawn::BeginPlay() {
	Super::BeginPlay();
	qp_navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	qp_spawnTime = 10* FMath::FRandRange(0.f, 1.f);

	//DrawDebugSphere(
	//	GetWorld(),
	//	GetActorLocation(),
	//	200.f,
	//	24,
	//	FColor::Green,
	//	true   // 持久显示（编辑器）
	//);

}


void AQP_AutoSpawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	qp_spawnTime -= DeltaTime;
	if (qp_spawnTime <= 0) {
		qp_spawnTime = qp_spawnTimeMin + qp_spawnTimeRange * FMath::FRandRange(0.f, 1.f);
		QP_Spawn();
	}

}

AActor* AQP_AutoSpawn::QP_Spawn() {
	//UNavigationSystemV1* NavSys = 
	/*if (!qp_target) {
		return false;
	}*/
	if (qp_navSys)
	{

		FNavLocation Result;

		bool bFound = qp_navSys->GetRandomReachablePointInRadius(GetActorLocation(), qp_radius, Result);
		if (bFound)
		{
			//qp_runTarget = Result.Location;
			//qp_isRunTarget = true;
			//return true;
			FActorSpawnParameters qp_spawnP;
			qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			//GetWorld()->SpawnActor<AActor>()
			return GetWorld()->SpawnActor<AActor>(qp_spawnActor, Result.Location,FRotator(0,0,0), qp_spawnP);
			
			// 你可以用这个 RandomLocation 来移动
			//MoveToLocation(RandomLocation); // 示例
		}
	}
	return nullptr;

}

#if WITH_EDITOR
void AQP_AutoSpawn::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);

	const FName PropName =
		Event.Property ? Event.Property->GetFName() : NAME_None;

	if (PropName == GET_MEMBER_NAME_CHECKED(AQP_AutoSpawn, qp_radius))
	{
		qp_showSphere->SetSphereRadius(qp_radius);
		qp_showSphere->MarkRenderStateDirty();
	}
}
#endif