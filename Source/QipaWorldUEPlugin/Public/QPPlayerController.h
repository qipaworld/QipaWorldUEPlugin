// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/QPGIM_BaseData.h"
#include "QPPlayerController.generated.h"

class UInputMappingContext;

class UInputAction;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void QP_OnAutoUIKeyPressed();
	void QP_OnOpenPlayerInformation();
	void QP_OnOpenBackpack();
	void QP_OnOpenMap();
	void QP_OnPickUp();
	void QP_OnOpenPlayerSkill();

	void QP_SwitchMouseShow();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")
	//FName qp_savePlayerDataName = "qp_savePlayerDataName";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TArray<TObjectPtr<UInputMappingContext>> qp_inputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TObjectPtr<UInputAction> qp_debugSwitchMouseShowInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TObjectPtr<UInputAction> qp_debugDefaultUserInterfaceAction;

	//qppop d  UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_openDefaultUIAction = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	TSubclassOf<UUserWidget> qp_openDefaultUI;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_openPlayerInformation = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	TSubclassOf<UUserWidget> qp_openPlayerInformationUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_openMap = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	TSubclassOf<UUserWidget> qp_openMapUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_openPlayerSkill = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	TSubclassOf<UUserWidget> qp_openPlayerSkillUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_openBackpack = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	TSubclassOf<UUserWidget> qp_openBackpackUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")

	TObjectPtr<UInputAction> qp_pickUp = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|UI")
	//TSubclassOf<UUserWidget> qp_pickUpUI;

	//UQPData* qp_savePlayerData;
	//virtual void QP_LoadData();
	//virtual void QP_SaveData();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
