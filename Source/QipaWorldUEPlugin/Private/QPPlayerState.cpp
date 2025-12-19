// QIPAWORLD


#include "QPPlayerState.h"




void AQPPlayerState::BeginPlay() {
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 1"));
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::BeginPlaye______ 2"));

}
void  AQPPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 1"));
    Super::EndPlay(EndPlayReason);
    //UE_LOG(LogTemp, Warning, TEXT("AQPPlayerState::EndPlay______ 2"));
}