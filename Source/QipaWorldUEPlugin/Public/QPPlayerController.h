// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	void QP_SwitchMouseShow();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TArray<TObjectPtr<UInputMappingContext>> qp_inputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TObjectPtr<UInputAction> qp_debugSwitchMouseShowInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|input")

	TObjectPtr<UInputAction> qp_debugDefaultUserInterfaceAction;

	

	
};
