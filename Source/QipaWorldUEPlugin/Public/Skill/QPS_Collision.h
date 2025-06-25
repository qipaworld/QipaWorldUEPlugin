// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPSkill.h"
#include "Components/SphereComponent.h"
#include "QPS_Collision.generated.h"

/**
 * 可碰撞的技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPS_Collision : public AQPSkill
{
	GENERATED_BODY()
protected:
		/**由于爆炸后有特效，所以延迟销毁*/
	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPSlimeAttack")
		float qp_bustDestroy = 2;

public:
	// Sets default values for this actor's properties
	AQPS_Collision();

protected:
	/**碰撞体*/
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSkillCollision")
	USphereComponent* qp_sphere;

	/**碰到物体时的特效技能特效*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QipaWorld|QPSkillCollision", Meta = (ShortTooltip = "技能碰撞物体时的特效"))
		UNiagaraComponent* qp_bustNiagara;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void QP_End() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void QP_OnSkillOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		virtual void QP_OnSkillOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		virtual void QP_OnSkillHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
