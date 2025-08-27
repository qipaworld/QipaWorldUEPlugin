// QIPAWORLD


#include "QPPlayerController.h"
#include "Data/QPGIM_Data.h"
#include "QPUtil.h"
#include "GameFramework/GameUserSettings.h"
#include "Online/QPGI_Online.h"
#include "Data/QPGIM_BaseData.h"

void AQPPlayerController::BeginPlay() {
    Super::BeginPlay();
    if (!UQPGIM_BaseData::qp_staticObject->QP_IsInitKey("QP_AutoSetingGameQuality")) {
        UGameUserSettings* Settings = GEngine->GetGameUserSettings();
        Settings->SetDynamicResolutionEnabled(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DynamicResolutionEnabled); 
        Settings->ApplySettings(false);               
        Settings->SaveSettings();                     

        if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_AutoSetingGameQuality) {
            UQPUtil::QP_AutoSetingGameQuality();
        }
        UQPGIM_BaseData::qp_staticObject->QP_SetInitKey("QP_AutoSetingGameQuality", true);
    }
    UQPGIM_BaseData::qp_staticObject->QP_GetSoundData()->QP_Addbool("ActivateBusMix", true);
    //UQPGIM_BaseData::qp_staticObject->QP_GetUIEventData()->QP_Addbool("AddMainUI", true);
    UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("AddMainUI", true, EQPDataBroadcastType::DEFAULT);

    

    
    UQPGI_Online::qp_staticObject->QP_Init();
           
     
      
        
}
void AQPPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent); 

    if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_UserInterfaceAutoPop) {
        InputComponent->BindAction(*(UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_DefaultUserInterfaceActionKey), IE_Released, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
        if (GIsEditor)
        {
            InputComponent->BindAction("DebugDefaultUserInterfaceAction", IE_Released, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
        }
    }
}

void AQPPlayerController::QP_OnAutoUIKeyPressed()
{
    UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("autoPushAndPopUI", true,EQPDataBroadcastType::SYNC);    
}
