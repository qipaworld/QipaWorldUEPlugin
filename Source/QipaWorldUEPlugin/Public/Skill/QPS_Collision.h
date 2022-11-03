// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Skill/QPSkill.h"
#include "Components/StaticMeshComponent.h"

#include "QPS_Collision.generated.h"

/**
 * 可移动的技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPS_Collision : public AQPSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPS_Collision();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* qp_staticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
