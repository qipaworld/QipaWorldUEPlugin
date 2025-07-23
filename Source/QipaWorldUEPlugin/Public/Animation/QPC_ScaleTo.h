// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/QPC_Scale.h"
#include "QPC_ScaleTo.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_ScaleTo : public UQPC_Scale
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	FVector qp_targetScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	float qp_time = 0;
public:
	// Sets default values for this component's properties
	//UQPC_ScaleTo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void QP_TickAnim() override;

	UFUNCTION(BlueprintCallable)
	void QP_SetScaleTarget(const FVector& c);

};
