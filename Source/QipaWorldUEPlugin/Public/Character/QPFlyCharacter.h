// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Character/QPCharacter.h"
#include "QPFlyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPFlyCharacter : public AQPCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQPFlyCharacter();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_moveUp = "MoveUp";

	float qp_moveUpV = 0.0f;
	FRotator qp_lastRotator;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		//float qp_upSpeed = 250.0f;


	virtual void QP_MoveForward(float value)override;
	virtual void QP_MoveRight(float value)override;

	virtual void QP_MoveUp(float value);
	/**更新移动速度，大了就跑，小了就走*/
	virtual void QP_UpdateMaxSpeed()override;

};
