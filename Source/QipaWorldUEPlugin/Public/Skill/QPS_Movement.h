// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPSkill.h"
#include "QPS_Movement.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
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
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* qp_staticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
