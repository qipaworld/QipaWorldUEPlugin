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
#include "Data/QPData.h"

#include "Notify/QPGIM_AnimNotifyData.h"


AQPFlyCharacter::AQPFlyCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	qp_movementMode = MOVE_Flying;
	qp_unchangeMovementMode = true;
}

// Called when the game starts or when spawned
void AQPFlyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//qp_lastRotator = GetActorRotation();
	qp_movementC->MaxFlySpeed = qp_walkSpeed;
	qp_movementC->SetMovementMode(MOVE_Flying);
}

void AQPFlyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ue  bug 在设置z轴上升的时候会自己旋转，所以我把他转回来了。
	FVector v = GetLastMovementInputVector();
	if (v.X != 0 || v.Y != 0) {
		qp_lastRotatorYaw = GetActorRotation().Yaw;
	}
	else if (qp_moveUpV != 0 && !qp_isFixedCamera) {
		FRotator r = GetActorRotation();
		r.Yaw = qp_lastRotatorYaw;
		SetActorRotation(r);
	}
	 
	

}

// Called to bind functionality to input
void AQPFlyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(qp_moveUp, this, &AQPFlyCharacter::QP_MoveUp);
	
}

void AQPFlyCharacter::QP_MoveUp(float value)
{
	qp_moveUpV = value;
	if (value != 0) {
		//QP_UpdateMaxSpeed();
		//FRotator Rotation = Controller->GetControlRotation();
		//Rotation.Roll = 0.0f;
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get up vector
		//const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Z);
		//AddMovementInput(Direction, value);
		//FRotator rotator = GetControlRotation();
		//rotator.Roll = 0.0f;
		//rotator.Yaw = 0.0f;
		//rotator.Pitch = 0.0f;
		//AddActorLocalOffset(FVector(0, 0,GetWorld()->DeltaTimeSeconds * qp_upSpeed * value));

		AddMovementInput(FVector::UpVector, value);
		//qp_lastRotator = GetActorRotation();

	}
}
void AQPFlyCharacter::QP_UpdateMaxSpeed() {

	GetCharacterMovement()->MaxFlySpeed = FMath::FInterpTo(GetCharacterMovement()->MaxFlySpeed, qp_maxSpeed, GetWorld()->GetDeltaSeconds(), 0.5f);
}
void AQPFlyCharacter::QP_MoveForward(float value)
{
	qp_forwardV = value;

	if (value != 0) {
		QP_UpdateMaxSpeed();
		FRotator rotator = GetControlRotation();
		//rotator.Roll = 0.0f;
		//rotator.Pitch = 0.0f;
		AddMovementInput(rotator.Vector(), value);
		//qp_lastRotator = GetActorRotation();

	}

	// animInst->PlaySlotAnimation(animSequence,"Slime_Anim_Armature_ForwardMove");
}

void AQPFlyCharacter::QP_MoveRight(float value)
{
	qp_rightV = value;
	if (value != 0) {
		QP_UpdateMaxSpeed();
		FRotator rotator = GetControlRotation();
		//rotator.Roll = 0.0f;
		//rotator.Pitch = 0.0f;

		FVector rightVector = FRotationMatrix(rotator).GetScaledAxis(EAxis::Y);
		AddMovementInput(rightVector, value);

	}
}

void AQPFlyCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);

}