// QIPAWORLD


#include "QPGameInstance.h"

void UQPGameInstance::Init() {
	//UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Init______ 1"));

	Super::Init();
	//UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Init______ 2"));

}


 /**  function to allow custom GameInstances an opportunity to do cleanup when shutting down */
 void UQPGameInstance::Shutdown(){
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Shutdown______ 1"));
	 //
	 Super::Shutdown();
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Shutdown______ 2"));

 }
 void UQPGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld){
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::OnWorldChanged______ 1"));

	 Super::OnWorldChanged(OldWorld, NewWorld);
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::OnWorldChanged______ 2"));

 }

 /** Starts the GameInstance state machine running */
 void UQPGameInstance::StartGameInstance(){
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Init______ 1"));

	 Super::StartGameInstance();
	 //UE_LOG(LogTemp, Warning, TEXT("UQPGameInstance::Init______ 1"));

 }