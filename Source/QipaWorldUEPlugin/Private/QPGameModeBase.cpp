// QIPAWORLD


#include "QPGameModeBase.h"

void AQPGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	//UE_LOG(LogTemp, Warning, TEXT("AQPGameModeBase::InitGam______ 1"));

		Super::InitGame(MapName, Options, ErrorMessage);
	//UE_LOG(LogTemp, Warning, TEXT("AQPGameModeBase::InitGam______ 2"));
}

void AQPGameModeBase::InitGameState(){
	//UE_LOG(LogTemp, Warning, TEXT("AQPGameModeBase::InitGameState______ 1"));
	Super::InitGameState();
	//UE_LOG(LogTemp, Warning, TEXT("AQPGameModeBase::InitGameState______ 2"));
}
