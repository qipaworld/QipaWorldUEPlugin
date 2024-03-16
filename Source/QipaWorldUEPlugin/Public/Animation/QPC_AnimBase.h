// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "QPC_AnimBase.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_AnimBase : public UQPComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	float qp_xSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	float qp_ySpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	float qp_zSpeed = 0;
	//是否自动播放
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	bool qp_autoPlay = true;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	//bool qp_isRelative = true;
	AActor* qp_owner = nullptr;

	float qp_tickTime = 0;
public:
	// Sets default values for this component's properties
	UQPC_AnimBase();

//protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void QP_TickAnim() {};

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPAnim")
	virtual void QP_Play();
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPAnim")
	virtual void QP_Stop();
};
