// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QPA_Sun.generated.h"

/**
 * 一个昼夜交替的太阳
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Sun : public AQPActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPA_Sun();

//protected:
	//太阳的移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSun")
	float qp_speed = 10.0f;
	//如果是真，则太阳为静止状态。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSun")
	bool qp_static = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void ttt();
};
