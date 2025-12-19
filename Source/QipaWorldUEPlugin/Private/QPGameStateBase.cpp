// QIPAWORLD


#include "QPGameStateBase.h"


void AQPGameStateBase::BeginPlay() {
    //UE_LOG(LogTemp, Warning, TEXT("AQPGameStateBase::BeginPlaye______ 1"));
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("AQPGameStateBase::BeginPlaye______ 2"));

}
void  AQPGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    //UE_LOG(LogTemp, Warning, TEXT("AQPGameStateBase::EndPlay______ 1"));
    Super::EndPlay(EndPlayReason);
    //UE_LOG(LogTemp, Warning, TEXT("AQPGameStateBase::EndPlay______ 2"));
}