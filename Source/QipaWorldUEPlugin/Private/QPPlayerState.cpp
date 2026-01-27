// QIPAWORLD


#include "QPPlayerState.h"
#include "Item/QPSG_ItemBackpack.h"




void AQPPlayerState::BeginPlay() {
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 1"));
    Super::BeginPlay();
    qp_itemBackpackSaveData = UQPSaveGame::QP_LoadSaveData<UQPSG_ItemBackpack>("qp_itemBackpackSaveData", 0);
    qp_itemBackpackSaveData->AddToRoot();
    qp_itemFoods = qp_itemBackpackSaveData->qp_itemFoods;
    qp_itemTransforms = qp_itemBackpackSaveData->qp_itemTransforms;

    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 2"));

}
void  AQPPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason) {
     qp_itemBackpackSaveData->qp_itemFoods = qp_itemFoods;
     qp_itemBackpackSaveData->qp_itemTransforms = qp_itemTransforms;
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 1"));
    qp_itemBackpackSaveData->QP_Save();
    Super::EndPlay(EndPlayReason);
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 2"));
}