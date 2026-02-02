// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Components/BoxComponent.h"
#include "Monster/QPMonster.h"

#include "QP_PlayerTrigger.generated.h"

/**
 * 
 */

UCLASS()
class QIPAWORLDUEPLUGIN_API AQP_PlayerTrigger : public AQPActor
{
	GENERATED_BODY()
	
public:
	AQP_PlayerTrigger();
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* qp_triggerBox;
	

	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
};
