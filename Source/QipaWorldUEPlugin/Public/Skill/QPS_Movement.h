// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPSkill.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "QPS_Movement.generated.h"

/**
 * 可移动的技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPS_Movement : public AQPSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPS_Movement();

protected:
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* qp_movement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** 获得移动组件*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillMovement")
		UProjectileMovementComponent* QP_GetMovement();

	/** 设置新的自身移动速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillMovement")
		void SetMoveVelocityInLocalSpace(FVector NewVelocity);

	/** 设置移动最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillMovement")
		void QP_SetMaxMoveSpeed(float speed);

	/** 给移动添加力*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillMovement")
		void QP_AddMoveForce(FVector NewVelocity);

	/** 未启用的方法，不知道用途*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	//void QP_AddLimitForce(FVector NewVelocity);

	/** 在自身的速度上添加速度*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	//void QP_AddMoveSpeed(FVector NewVelocity);
	/**在前进方向上添加速度*/
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	//void QP_AddMoveSpeedFloat(float speed);
	/** 在自身的速度上添加速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillMovement")
		void QP_AddMoveVelocity(FVector NewVelocity);
};
