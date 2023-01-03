// QIPAWORLD


#include "Character/QPCharacter.h"

#include <complex.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Data/QPGIM_Data.h"
#include "UObject/UnrealType.h"
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"

// Sets default values
AQPCharacter::AQPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	qp_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	qp_springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	qp_springArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	qp_springArm->SetupAttachment(RootComponent);
	qp_camera->SetupAttachment(qp_springArm);
	

}

// Called when the game starts or when spawned
void AQPCharacter::BeginPlay()
{
	Super::BeginPlay();
	qp_playerData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData(qp_playerDataKey);
	qp_movementC = GetCharacterMovement();
	qp_movementC->bOrientRotationToMovement = true;
	qp_movementC->MaxAcceleration = qp_walkMaxAcceleration;
	qp_movementC->bRunPhysicsWithNoController = true;
	qp_movementC->MaxWalkSpeed = qp_walkSpeed;
	qp_isFixedCamera = false;
	qp_isRun = false;
}

// Called every frame
void AQPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(qp_moveForWard, this, &AQPCharacter::QP_MoveForward);
	PlayerInputComponent->BindAxis(qp_moveRight, this, &AQPCharacter::QP_MoveRight);
	PlayerInputComponent->BindAxis(qp_turn, this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(qp_lookUp, this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(qp_jump, IE_Pressed, this, &AQPCharacter::QP_JumpStart);
	PlayerInputComponent->BindAction(qp_jump, IE_Released, this, &AQPCharacter::QP_JumpEnd);
	PlayerInputComponent->BindAction(qp_run, IE_Pressed, this, &AQPCharacter::QP_RunStart);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AQPC_Slime::QP_RunEnd);
	PlayerInputComponent->BindAction(qp_attack, IE_Pressed, this, &AQPCharacter::QP_AttackStart);
	PlayerInputComponent->BindAction(qp_attack, IE_Released, this, &AQPCharacter::QP_AttackEnd);
	PlayerInputComponent->BindAction(qp_fixedCamera, IE_Pressed, this, &AQPCharacter::QP_FixedCamera);
	PlayerInputComponent->BindAction(qp_attackTwo, IE_Pressed, this, &AQPCharacter::QP_AttackTwoStart);
	PlayerInputComponent->BindAction(qp_attackTwo, IE_Released, this, &AQPCharacter::QP_AttackTwoEnd);
	PlayerInputComponent->BindAction(qp_mouseWheelUp, IE_Pressed, this, &AQPCharacter::QP_mouseWheelUp);
	PlayerInputComponent->BindAction(qp_mouseWheelDown, IE_Pressed, this, &AQPCharacter::QP_mouseWheelDown);

}

void AQPCharacter::QP_UpdateMaxSpeed() 
{
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, qp_maxSpeed , GetWorld()->GetDeltaSeconds(), 0.5f);
}

void AQPCharacter::QP_MoveForward(float value)
{
	 qp_forwardV = value;
	if (value != 0) {
		QP_UpdateMaxSpeed();
		FRotator rotator = GetControlRotation();
		rotator.Roll = 0.0f;
		rotator.Pitch = 0.0f;
		AddMovementInput(rotator.Vector(), value);

	}

	// animInst->PlaySlotAnimation(animSequence,"Slime_Anim_Armature_ForwardMove");
}

void AQPCharacter::QP_MoveRight(float value)
{
	qp_rightV = value;
	if (value != 0) {
		QP_UpdateMaxSpeed();
		FRotator rotator = GetControlRotation();
		rotator.Roll = 0.0f;
		rotator.Pitch = 0.0f;

		FVector rightVector = FRotationMatrix(rotator).GetScaledAxis(EAxis::Y);
		AddMovementInput(rightVector, value);
	}
}

void AQPCharacter::QP_Run() 
{
	qp_isRun = !qp_isRun;
	if (qp_isRun) {
		QP_RunStart();
	}
	else {
		QP_RunEnd();
	}
}

 void AQPCharacter::QP_RunStart()
 {
	 qp_maxSpeed = qp_runSpeed;
	 qp_movementC->MaxAcceleration = qp_runMaxAcceleration;

 }
 void AQPCharacter::QP_RunEnd()
 {
	 qp_maxSpeed = qp_walkSpeed;

	 qp_movementC->MaxAcceleration = qp_walkMaxAcceleration;

 }

//相机固定与自由的切换
 void AQPCharacter::QP_FixedCamera()
 {
	 qp_isFixedCamera = !qp_isFixedCamera;
	 qp_movementC->bOrientRotationToMovement = !qp_isFixedCamera;
	 qp_movementC->bUseControllerDesiredRotation = qp_isFixedCamera;
	 if (qp_isFixedCamera) {
		 QP_FixedCameraStart();
	 }
	 else {
		 QP_FixedCameraEnd();
	 }
 }

 void AQPCharacter::QP_FixedCameraStart()
 {
	 

 }
 void AQPCharacter::QP_FixedCameraEnd()
 {
 }

//按下鼠标右键
 void AQPCharacter::QP_AttackTwoStart()
 {
 }
//松开鼠标右键
 void AQPCharacter::QP_AttackTwoEnd()
 {
 }

 void AQPCharacter::QP_JumpStart()
 {
	 //如果是真的话，角色跳跃
	 bPressedJump = true;
	 
 }
 void AQPCharacter::QP_JumpEnd()
 {
	 //如果是假的话，结束跳跃
	 bPressedJump = false;
	 //GLog->Log("jumpEnd");

 }

 void AQPCharacter::Landed(const FHitResult& Hit) {
	 Super::Landed(Hit);
 }


 void AQPCharacter::QP_AttackStart()
 {
 
 }

 void AQPCharacter::QP_AttackEnd()
 {
	
 }

 //攻击开始
 void  AQPCharacter::QP_mouseWheelUp() {

	 if (qp_springArm->TargetArmLength > qp_minCameraLength) {
		 qp_springArm->TargetArmLength = qp_springArm->TargetArmLength - qp_changeCameraLengthSpeed * GetWorld()->GetDeltaSeconds();
		 if (qp_springArm->TargetArmLength < qp_minCameraLength) {
			 qp_springArm->TargetArmLength = qp_minCameraLength;
		 }
		 if (qp_springArm->TargetArmLength < qp_visibleCameraMinLength) {
			 GetMesh()->SetVisibility(false);
		 }
	 }
 }
 //攻击结束
 void  AQPCharacter::QP_mouseWheelDown() {
	 if (qp_springArm->TargetArmLength < qp_maxCameraLength) {
		 qp_springArm->TargetArmLength = qp_springArm->TargetArmLength + qp_changeCameraLengthSpeed * GetWorld()->GetDeltaSeconds();
		 if (qp_springArm->TargetArmLength > qp_maxCameraLength) {
			 qp_springArm->TargetArmLength = qp_maxCameraLength;
		 }
		 if (qp_springArm->TargetArmLength > qp_visibleCameraMinLength) {
			 GetMesh()->SetVisibility(true);
		 }
	 }
 }