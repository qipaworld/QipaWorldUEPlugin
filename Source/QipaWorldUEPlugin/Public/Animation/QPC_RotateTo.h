// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/QPC_Rotate.h"
#include "QPC_RotateTo.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_RotateTo : public UQPC_Rotate
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	FRotator qp_targetRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	float qp_time = 0;
public:
	// Sets default values for this component's properties
	//UQPC_RotateTo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void QP_TickAnim() override;

};
