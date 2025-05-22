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
#include "Data/QPGIM_BaseData.h"


#include "Animation/QPC_MaterialAutoRestore.h"
#include "Monster/QPMonster.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "QPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class UQPData;
class UAnimInstance;
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPCharacter : public AQPMonster
{
	GENERATED_BODY()

	
public:
	// Sets default values for this character's properties
	AQPCharacter();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * Called when an instance of this class is placed (in editor) or spawned.
	 * @param	Transform			The transform the actor was constructed at.
	 */
	//virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;
	/**初始化数据*/
	//virtual void QP_InitQPData() override;
	/**获得数据*/
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "QipaWorld|QPInterface")
	

public:

	

	
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName qp_mouseWhellAxis = "MouseWhell";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName qp_changeCharacter = "ChangeCharacter";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_moveForWard = "MoveForWard";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_moveRight = "MoveRight";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_turn = "Turn";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_lookUp = "LookUp";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_jump = "Jump";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_run = "Run";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName qp_attack = "Attack";
		/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName qp_sneak = "Sneak";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_mouseWheelUp = "MouseWheelUp";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_mouseWheelDown = "MouseWheelDown";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_attackTwo = "AttackTwo";
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_fixedCamera = "FixedCamera";

	

	


	
	/**玩家移动模式，切换玩家时用的*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		TEnumAsByte<EMovementMode> qp_movementMode = MOVE_Walking;
	/**攻击动画*/
	
	/**跳跃动画*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		//UQPC_PlayMontage* qp_playJumpAnim;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		//bool  qp_unchangeMovementMode = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		FName qp_changeCharacterName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		bool qp_unchangeMovementMode = true;
	

	/*是否自动弹簧臂长度*/
	bool qp_isAutoCameraLength = false;
	/*目标弹簧臂长度*/
	float qp_targetCameraLength = 0.0f;

	/**相机最大距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		float qp_maxCameraLength = 1200.0f;
	/**显示玩家网格最小距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		float qp_visibleCameraMinLength = 10.0f;
	/**相机最小距离*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		float qp_minCameraLength = 0.0f;
	/**鼠标滚轮改变相机距离的速度*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		float qp_changeCameraLengthSpeed = 20.0f;
	
	/**是否固定相机*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
		bool qp_isFixedCamera = false;

		

	bool qp_isFixedCameraLast = false;
	bool qp_isRunLast = false;

	bool qp_isReset = false;
	bool qp_isExit = false;
	

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPCharacter")
		UCameraComponent* qp_camera;

	UPROPERTY(VisibleAnywhere, Category = "QipaWorld|QPCharacter")
		USpringArmComponent* qp_springArm;

	

	

	
public:
	//简单的重置一下
	virtual void QP_Reset();
	//撤销简单的重置
	virtual void QP_ReReset();
	//脱离玩家控制时调用
	virtual void QP_PlayerExit();
	//进入玩家控制时调用
	virtual void QP_PlayerEnter();

	virtual void QP_MouseWheelAxis(float value);
	virtual void QP_TrunAxis(float value);
	virtual void QP_LookUpAxis(float value);

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

	//前行的切换
	virtual void QP_Sneak();
	virtual void QP_SneakStart();
	virtual void QP_SneakEnd();

	virtual void QP_ChangeCharacter();

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
	virtual inline void QP_UpdateMaxSpeed() {
		if (qp_movementC->MaxWalkSpeed != qp_maxSpeed) {
			qp_movementC->MaxWalkSpeed = FMath::FInterpTo(qp_movementC->MaxWalkSpeed, qp_maxSpeed, GetWorld()->GetDeltaSeconds(), qp_moveInterpSpeed);
		}
	}

	/**创建魔法技能*/
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPCharacter")
		virtual void QP_Fire();

	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPCharacter")
	virtual void QP_SetMatAmount(float amount = 0.f);

	/**监听蒙太奇事件*/
	virtual void QP_AnimNotifyEvent(UQPData* data);
	/**监听跳跃动画播放结束事件*/
	//virtual void QP_AnimNotifyJumpEnd(UQPData* data);
};
