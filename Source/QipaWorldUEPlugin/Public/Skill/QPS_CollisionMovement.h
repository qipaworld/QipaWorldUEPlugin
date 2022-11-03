// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPSkill.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "QPS_CollisionMovement.generated.h"

/**
 * 可移动的技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPS_CollisionMovement : public AQPSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPS_CollisionMovement();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* qp_staticMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* qp_movement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
