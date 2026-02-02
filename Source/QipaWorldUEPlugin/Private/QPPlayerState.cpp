// QIPAWORLD


#include "QPPlayerState.h"
#include "Item/QPSG_ItemBackpack.h"
#include "Item/QPA_Item.h"



void AQPPlayerState::BeginPlay() {
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 1"));
    Super::BeginPlay();
    qp_itemBackpackSaveData = UQPSaveGame::QP_LoadSaveData<UQPSG_ItemBackpack>("qp_itemBackpackSaveData", 0);
    qp_itemBackpackSaveData->AddToRoot();
    qp_itemFoods = qp_itemBackpackSaveData->qp_itemFoods;
    int i = 159 - qp_itemFoods.Num();

    while(i>0){
        i--;
        qp_itemFoods.Add(FQPItem());
    }
    int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp();
    for (auto& v : qp_itemFoods)
    {
        v.qp_createTime = TimestampMs - v.qp_lastTime;
        

    }
    //qp_itemTransforms = qp_itemBackpackSaveData->qp_itemTransforms;

    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 2"));

}
void  AQPPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp();

    for (auto& v: qp_itemFoods)
    {
        v.qp_lastTime = TimestampMs - v.qp_createTime;
        

    }
   
     qp_itemBackpackSaveData->qp_itemFoods = qp_itemFoods;
     //qp_itemBackpackSaveData->qp_itemTransforms = qp_itemTransforms;
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 1"));
    qp_itemBackpackSaveData->QP_Save();
    Super::EndPlay(EndPlayReason);
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 2"));
}