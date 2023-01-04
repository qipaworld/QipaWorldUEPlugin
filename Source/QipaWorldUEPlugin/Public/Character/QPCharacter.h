// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraActor.h"
#include "Skill/QPS_CollisionMovement.h"
#include "Component/QPSComponent.h"

#include "QPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class UQPData;
class UAnimInstance;
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQPCharacter();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;
public:
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_moveForWard = "MoveForWard";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_moveRight = "MoveRight";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_turn = "Turn";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_lookUp = "LookUp";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_jump = "Jump";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_run = "Run";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_attack = "Attack";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_mouseWheelUp = "MouseWheelUp";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_mouseWheelDown = "MouseWheelDown";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_attackTwo = "AttackTwo";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FName qp_fixedCamera = "FixedCamera";

	/**数据名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		FString qp_playerDataKey = "qp_playerData";
	/**玩家数据*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		UQPData* qp_playerData;
	/**玩家移动模式，切换玩家时用的*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		TEnumAsByte<EMovementMode> qp_movementMode = MOVE_Walking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		bool  qp_unchangeMovementMode = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_walkSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_runSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_walkMaxAcceleration = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_runMaxAcceleration = 600.0f;
	/**最大速度是run就是跑，是walk就是走路*/
	float qp_maxSpeed = 250.0f;
	/**相机最大距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_maxCameraLength = 1200.0f;
	/**显示玩家网格最小距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_visibleCameraMinLength = 10.0f;
	/**相机最小距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_minCameraLength = 0.0f;
	/**鼠标滚轮改变相机距离的速度*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		float qp_changeCameraLengthSpeed = 20.0f;
	/**是否在跑*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		bool qp_isRun = false;
	/**是否在跑*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
		bool qp_isFixedCamera = false;

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSlime")
		UCameraComponent* qp_camera;

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPSlime")
		USpringArmComponent* qp_springArm;

	UCharacterMovementComponent* qp_movementC;

	float qp_forwardV = 0.0f;
	float qp_rightV = 0.0f;
public:
	virtual void QP_MoveForward(float value);
	virtual void QP_MoveRight(float value);
	//跳跃开始
	virtual void QP_JumpStart();
	//跳跃结束
	virtual void QP_JumpEnd();
	//跑与走的切换
	virtual void QP_Run();
	
	virtual void QP_RunStart();
	virtual void QP_RunEnd();

	//相机固定与自由的切换
	virtual void QP_FixedCamera();

	virtual void QP_FixedCameraStart();
	virtual void QP_FixedCameraEnd();

	//按下鼠标左键
	virtual void QP_AttackStart();
	//松开鼠标左键
	virtual void QP_AttackEnd();

	//按下鼠标右键
	virtual void QP_AttackTwoStart();
	//松开鼠标右键
	virtual void QP_AttackTwoEnd();

	//相机靠近角色
	virtual void QP_mouseWheelUp();
	//相机远离角色
	virtual void QP_mouseWheelDown();

	/**更新移动速度，大了就跑，小了就走*/
	virtual void QP_UpdateMaxSpeed();
};
