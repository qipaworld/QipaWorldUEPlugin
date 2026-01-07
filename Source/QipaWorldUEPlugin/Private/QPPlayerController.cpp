// QIPAWORLD


#include "QPPlayerController.h"
#include "Data/QPGIM_Data.h"
#include "QPUtil.h"
#include "GameFramework/GameUserSettings.h"
#include "Online/QPGI_Online.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Data/QPGIM_PlayerData.h"
#include "Data/QPGIM_BaseData.h"
#include "UserInterface/QPGIM_UserInterface.h"


void AQPPlayerController::BeginPlay() {
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerController::BeginPlaye______ 1"));
    Super::BeginPlay();
    if (IsLocalPlayerController()) {
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

        UQPGI_Online::qp_staticObject->QP_Init();

        if (UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getbool("qp_autoControllerRotation")) {
            SetControlRotation(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFRotator("ControllerRotation"));
        }
        
        UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Addbool("qp_autoControllerRotation", true);
        
    }
    
    //UQPGIM_BaseData::qp_staticObject->QP_GetSoundData()->QP_Addbool("ActivateBusMix", true);
    //UQPGIM_BaseData::qp_staticObject->QP_GetUIEventData()->QP_Addbool("AddMainUI", true);
    // this move to QPHUD 
    //UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("AddMainUI", true, EQPDataBroadcastType::DEFAULT);




    
    //QP_LoadData();

    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerController::BeginPlaye______ 2"));

}

void  AQPPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    if (IsLocalController()) {
        
        UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_AddFRotator("ControllerRotation", GetControlRotation());
        
        UQPGIM_PlayerData::qp_staticObject->QP_SaveLocalData();
    }
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerController::EndPlay______ 1"));

    Super::EndPlay(EndPlayReason);
    //QP_SaveData();
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerController::EndPlay______ 2"));
}
void AQPPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    
    check(InputComponent); 

    //if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        //if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
            {
                //Subsystem->RemoveMappingContext(DefaultMappingContext);
                for (auto v : qp_inputMappingContext) {
                    Subsystem->AddMappingContext(v,0);
                }
            }
        }
    }

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
    //Input->BindAction()
    if (qp_debugSwitchMouseShowInputAction) {

        Input->BindAction(qp_debugSwitchMouseShowInputAction, ETriggerEvent::Started, this, &AQPPlayerController::QP_SwitchMouseShow);
    }

    //if (UQPGIM_BaseData::qp_staticObject->qp_defaultDataAsset->QP_UserInterfaceAutoPop) {
        if (qp_openDefaultUIAction) {

            Input->BindAction(qp_openDefaultUIAction, ETriggerEvent::Started, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
        }
        if (GIsEditor)
        {
            if (qp_debugDefaultUserInterfaceAction) {

                Input->BindAction(qp_debugDefaultUserInterfaceAction, ETriggerEvent::Started, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
            }
            //InputComponent->BindAction("DebugDefaultUserInterfaceAction", IE_Released, this, &AQPPlayerController::QP_OnAutoUIKeyPressed);
        }
    //}
    if (qp_openPlayerInformation) {
        Input->BindAction(qp_openPlayerInformation, ETriggerEvent::Started, this, &AQPPlayerController::QP_OnOpenPlayerInformation);
    }
}

void AQPPlayerController::QP_OnAutoUIKeyPressed()
{
    UQPGIM_UserInterface::qp_staticObject->QP_AutoPopOrPushByClass(qp_openDefaultUI);
   // UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("autoPushAndPopUI", true,EQPDataBroadcastType::SYNC);    
}
void AQPPlayerController::QP_OnOpenPlayerInformation() {

   /* TSubclassOf<UUserWidget> w = qp_openPlayerInformationUI.Get();
    if (!IsValid(w)) {
        w = qp_openPlayerInformationUI.LoadSynchronous();
    }
    if (IsValid(w)) {
        return QP_AddUserInterfaceByClass(w, key);
    }*/
    
    UQPGIM_UserInterface::qp_staticObject->QP_AutoPopOrPushByClassEx(qp_openPlayerInformationUI,"qp_openPlayerInformationUI");
    //UQPGIM_BaseData::qp_staticObject->QP_GetKeyBoardEventData()->QP_Addbool("autoPushAndPopUI", true, EQPDataBroadcastType::SYNC);
}
void AQPPlayerController::QP_SwitchMouseShow() {
    UQPUtil::QP_SwitchMouseShow(this);
}

void AQPPlayerController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);

    //if (UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getbool("qp_autoControllerRotation")) {
        //SetControlRotation(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFRotator("ControllerRotation"));
        //qp_springArm->TargetArmLength = UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getfloat("TargetArmLength");
    //}
}
//void AQPPlayerController::QP_LoadData() {
//    qp_savePlayerData = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_GetUQPData(qp_savePlayerDataName);
//    qp_savePlayerData->QP_LoadDataFAES("AQPPlayerControllerPlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("AQPPlayerControllerPlayerDataSaveA"));
//}
//void AQPPlayerController::QP_SaveData() {
//
//    qp_savePlayerData->QP_SaveDataFAES("AQPPlayerControllerPlayerDataSave", UQPGIM_BaseData::qp_staticObject->GetAESKey("AQPPlayerControllerPlayerDataSaveA"));
//}

