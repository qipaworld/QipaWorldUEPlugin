// QIPAWORLD


#include "Monster/QPCharacterMovementComponent.h"

void UQPCharacterMovementComponent::HandleImpact(const FHitResult& Impact, float TimeSlice, const FVector& MoveDelta)
{
    Super::HandleImpact(Impact, TimeSlice, MoveDelta);

    if (qp_data) {
        qp_data->QP_Addbool("qp_movementBump", true,EQPDataBroadcastType::SYNC);
    }
}