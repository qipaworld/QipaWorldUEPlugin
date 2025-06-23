// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Sound/QPC_PlayRandomSound.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Chaos/ChaosNotifyHandlerInterface.h"
#include "QPA_ChaosDestructible.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_ChaosDestructible : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_ChaosDestructible();

	virtual void BeginPlay() override;
	UFUNCTION()
	void QP_OnChunkHit(const FChaosPhysicsCollisionInfo& CollisionInfo);
	UFUNCTION()
	void QP_OnBroken(const FChaosBreakEvent& BreakEvent);

	//UFUNCTION()
	//void QP_OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UAudioComponent* qp_footstepAudio = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UQPC_PlayRandomSound* qp_playRandomSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_maxSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	float qp_minVolume = 0.2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QipaWorld|ChaosDestructible")
	float qp_minVelocity = 50;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QipaWorld|ChaosDestructible")
	float qp_delayDestroy = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QipaWorld|ChaosDestructible")
	TObjectPtr<UGeometryCollectionComponent> qp_geometryCollection;
	
};
