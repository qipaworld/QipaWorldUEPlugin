// QIPAWORLD


#include "QPPlayerController.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPGIM_BaseData.h"

void AQPPlayerController::BeginPlay() {
    Super::BeginPlay();

    UQPGIM_BaseData::qp_staticObject->QP_GetSoundData()->QP_Addbool("ActivateBusMix", true);
}
void AQPPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent); 

    if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_UserInterfaceAutoPop) {
        InputComponent->BindAction(*(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey), IE_Released, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
    }
}

void AQPPlayerController::QP_OnAutoUIKeyPressed()
{
    UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("autoPushAndPopUI", true,EQPDataBroadcastType::SYNC);    
}
