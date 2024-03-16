// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/QPC_AnimBase.h"

#include "QPC_Move.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QIPAWORLDUEPLUGIN_API UQPC_Move : public UQPC_AnimBase
{
	GENERATED_BODY()
public:
	
	//FVector qp_vector;
	FVector qp_vectorSpeed;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	//FVector qp_vectorSpeed;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Animation")
	//float qp_sleepTime = 0;
public:	
	// Sets default values for this component's properties
	//UQPC_Move();

//protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void QP_TickAnim() override;

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPAnim")
	//virtual void QP_Play() override;
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPAnim")
	//virtual void QP_Stop() override;
		
};
