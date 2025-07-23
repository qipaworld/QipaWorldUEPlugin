// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Animation/QPC_AnimBase.h"

#include "QPC_Scale.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_Scale : public UQPC_AnimBase
{
	GENERATED_BODY()
public:
	
public:
	// Sets default values for this component's properties
	//UQPC_Scale();

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void QP_TickAnim() override;

};
