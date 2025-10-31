// QIPAWORLD

#include "Character/QPFlyCharacter.h"

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
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"


AQPFlyCharacter::AQPFlyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	qp_movementMode = MOVE_Flying;
	//qp_unchangeMovementMode = true;
}

// Called when the game starts or when spawned
void AQPFlyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//qp_lastRotator = GetActorRotation();
	qp_movementC->MaxFlySpeed = qp_walkSpeed;
	qp_movementC->SetMovementMode(MOVE_Flying);

	/*bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;*/
}

void AQPFlyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ue  bug 在设置z轴上升的时候会自己旋转，所以我把他转回来了。
	/*FVector v = GetLastMovementInputVector();
	if (v.X != 0 || v.Y != 0) {
		qp_lastRotatorYaw = GetActorRotation().Yaw;
	}
	else if (qp_moveUpV != 0 && !qp_isFixedCamera) {
		FRotator r = GetActorRotation();
		r.Yaw = qp_lastRotatorYaw;
		SetActorRotation(r);
	}*/
	 
	

}

// Called to bind functionality to input
void AQPFlyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Input->BindAction()
	
	
	//PlayerInputComponent->BindAxis(qp_moveUp, this, &AQPFlyCharacter::QP_MoveUp);
	
}

//void AQPFlyCharacter::QP_MoveUp(float value)
//{
//	qp_moveUpV = value;
//	if (value != 0) {
//		//QP_UpdateMaxSpeed();
//		//FRotator Rotation = Controller->GetControlRotation();
//		//Rotation.Roll = 0.0f;
//		//const FRotator YawRotation(0, Rotation.Yaw, 0);
//		// get up vector
//		//const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Z);
//		//AddMovementInput(Direction, value);
//		//FRotator rotator = GetControlRotation();
//		//rotator.Roll = 0.0f;
//		//rotator.Yaw = 0.0f;
//		//rotator.Pitch = 0.0f;
//		//AddActorLocalOffset(FVector(0, 0,GetWorld()->DeltaTimeSeconds * qp_upSpeed * value));
//
//		AddMovementInput(FVector::UpVector, value);
//		//qp_lastRotator = GetActorRotation();
//
//	}
//}
//void AQPFlyCharacter::QP_UpdateMaxSpeed() {
//
//	GetCharacterMovement()->MaxFlySpeed = FMath::FInterpTo(GetCharacterMovement()->MaxFlySpeed, qp_maxSpeed, GetWorld()->GetDeltaSeconds(), 0.5f);
//}
//void AQPFlyCharacter::QP_MoveUP(const FInputActionValue& value) {
//	//const float mv = ;
//	//qp_movementC->bOrientRotationToMovement = false;
//	qp_moveUpV = value.Get<float>();
//	AddMovementInput(FVector::UpVector, qp_moveUpV);
//	//qp_movementC->bOrientRotationToMovement = !qp_isFixedCamera;
//}
//void AQPFlyCharacter::QP_MoveRight(const FInputActionValue& value)
//{
//	
//	//FVector rightVector = FRotationMatrix(rotator).GetUnitAxis(EAxis::Y);
//	//AddMovementInput(rightVector, mv.X);
//	//AddMovementInput(FVector::UpVector, mv.Z);
//	//UQPUtil::QP_LOG(mv.ToString());
//	FRotator rotator = GetControlRotation();
//	//FVector v = rotator.Vector();
//	//FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
//	//FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
//	//AddMovementInput(v, mv.Y);
//	FVector rightVector = FRotationMatrix(rotator).GetUnitAxis(EAxis::Y);
//	AddMovementInput(rightVector, value.Get<float>());
//
//	// animInst->PlaySlotAnimation(animSequence,"Slime_Anim_Armature_ForwardMove");
//}
//
//void AQPFlyCharacter::QP_MoveForward(const FInputActionValue& value)
//{
//	//const FVector2D mv = value.Get<FVector2D>();
//	//const FVector2D mv = value.Get<FVector2D>();
//	FRotator rotator = GetControlRotation();
//	//FVector v = rotator.Vector();
//	//FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
//	//FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
//	AddMovementInput(rotator.Vector(), value.Get<float>());
//	//AddMovementInput(FVector::UpVector, mv.Z);
//	//UQPUtil::QP_LOG(mv.ToString());
//
//
//	// animInst->PlaySlotAnimation(animSequence,"Slime_Anim_Armature_ForwardMove");
//}
//void AQPFlyCharacter::QP_MoveRight(float value)
//{
//	qp_rightV = value;
//	if (value != 0) {
//	
//		FRotator rotator = GetControlRotation();
//		//rotator.Roll = 0.0f;
//		//rotator.Pitch = 0.0f;
//
//		FVector rightVector = FRotationMatrix(rotator).GetScaledAxis(EAxis::Y);
//		AddMovementInput(rightVector, value);
//
//	}
//}

void AQPFlyCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);

}