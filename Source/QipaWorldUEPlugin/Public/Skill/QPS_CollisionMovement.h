// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPS_Collision.h"
//#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "QPS_CollisionMovement.generated.h"

/**
 * 可移动的，可碰撞的，技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPS_CollisionMovement : public AQPS_Collision
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPS_CollisionMovement();

protected:
	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* qp_staticMesh;
	/**移动组件*/
	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSkillCollisionMovement")
	UProjectileMovementComponent* qp_movement;

	//UPROPERTY(VisibleAnywhere)
		//UStaticMeshComponent* qp_staticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** 获得移动组件*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillCollisionMovement")
	UProjectileMovementComponent* QP_GetMovement();

	/** 设置新的自身移动速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillCollisionMovement")
	void SetMoveVelocityInLocalSpace(FVector NewVelocity);

	/** 设置移动最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillCollisionMovement")
	void QP_SetMaxMoveSpeed(float speed);

	/** 给移动添加力*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillCollisionMovement")
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
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSkillCollisionMovement")
		void QP_AddMoveVelocity(FVector NewVelocity);
};
