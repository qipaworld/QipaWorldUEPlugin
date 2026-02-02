// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QP_PlayerTrigger.h"
#include "QP_TriggerUseAbility.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQP_TriggerUseAbility : public AQP_PlayerTrigger
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TArray<TSubclassOf<class UGameplayAbility>> qp_abilities;

	TArray<FGameplayAbilitySpecHandle> qp_abilityHandles;

	
	virtual void QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	virtual void QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
