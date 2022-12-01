// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPS_Collision.h"
//#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "QPS_CollisionMovement.generated.h"

/**
 * 可移动的技能的基类
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
	UPROPERTY(VisibleAnywhere)
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
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	UProjectileMovementComponent* QP_GetMovement();

	/** 添加速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_SetMoveSpeed(FVector NewVelocity);

	/** 在添加最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_SetMaxMoveSpeed(float speed);

	/** 在添加最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_AddMoveForce(FVector NewVelocity);

	/** 在添加最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_AddLimitForce(FVector NewVelocity);

	/** 在添加最大速度*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_AddMoveSpeed(FVector NewVelocity);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
	void QP_AddMoveSpeedFloat(float speed);

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|Skill")
		void QP_AddMoveVelocity(FVector NewVelocity);
};
