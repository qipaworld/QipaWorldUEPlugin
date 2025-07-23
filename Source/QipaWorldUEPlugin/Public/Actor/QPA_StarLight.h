// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Light/QPC_FadeLight.h"

#include "QPA_StarLight.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_StarLight : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_StarLight();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void QP_OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//virtual void QP_OnBroken(const FChaosBreakEvent& BreakEvent)override;
	//bool qp_isShow = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UStaticMeshComponent* qp_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|ChaosDestructible")
	UQPC_FadeLight* qp_fadeLight = nullptr;

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
	

	UFUNCTION(BlueprintCallable)
	void QP_FadeIn(float qp_maxTime_);
	UFUNCTION(BlueprintCallable)
	void QP_FadeOut();
	//virtual void QP_OnTriggerSimulatePhysicsBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//virtual void QP_OnTriggerSimulatePhysicsEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
