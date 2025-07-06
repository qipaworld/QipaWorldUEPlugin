// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/QPData.h"

#include "QPCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UQPData* qp_data = nullptr;
protected:
	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice = 0.f, const FVector& MoveDelta = FVector::ZeroVector) override;

};
