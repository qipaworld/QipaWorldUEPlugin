// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPA_ChaosDestructible.h"
#include "Material/QPC_FadeMaterials.h"

#include "QPA_DestructibleStarLight.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_DestructibleStarLight : public AQPA_ChaosDestructible
{
	GENERATED_BODY()
public:
	AQPA_DestructibleStarLight();

	virtual void BeginPlay() override;

	virtual void QP_OnChunkHit(const FChaosPhysicsCollisionInfo& CollisionInfo) override;

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//virtual void QP_OnBroken(const FChaosBreakEvent& BreakEvent)override;
	//bool qp_isShow = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UQPC_FadeMaterials* qp_fadeMaterials = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_fadeInTime = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_fadeOutTime = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	//float qp_delayTime = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_showTime = 3;
	float qp_showedTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_fadeInMinVelocity = 5;
	

	virtual void QP_OnTriggerSimulatePhysicsBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void QP_OnTriggerSimulatePhysicsEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
