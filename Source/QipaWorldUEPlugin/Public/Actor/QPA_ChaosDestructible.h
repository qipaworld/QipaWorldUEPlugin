// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Sound/QPC_PlayRandomSound.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Chaos/ChaosNotifyHandlerInterface.h"
#include "Components/SphereComponent.h"
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
	//UFUNCTION() //This is very slow and needs to be changed to pure Cpp when there is time
	 //void QP_OnChunkHit_Bind(const FChaosPhysicsCollisionInfo& CollisionInfo);
	//UFUNCTION()
	 //void QP_OnBroken_Bind(const FChaosBreakEvent& BreakEvent);

	 UFUNCTION()
	 virtual void QP_OnChunkHit(const FChaosPhysicsCollisionInfo& CollisionInfo);
	 UFUNCTION()
	 virtual void QP_OnBroken(const FChaosBreakEvent& BreakEvent);

	 
	 UFUNCTION()
	 virtual void QP_OnTriggerSimulatePhysicsBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 UFUNCTION()
	 virtual void QP_OnTriggerSimulatePhysicsEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION()
	//void QP_OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UAudioComponent* qp_footstepAudio = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UQPC_PlayRandomSound* qp_playRandomSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	bool qp_autoSimulatePhysics = true;

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
	
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSkillCollision")
	USphereComponent* qp_sphere;
	bool qp_isMove = false;
};
