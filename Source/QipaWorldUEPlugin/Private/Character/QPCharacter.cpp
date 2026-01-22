// QIPAWORLD


#include "Character/QPCharacter.h"

#include <complex.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Components/InputComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Data/QPGIM_Data.h"
#include "UObject/UnrealType.h"
#include "Data/QPData.h"
#include "QPUtil.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Character/QPGIM_Character.h"
#include "Character/QPDA_Character.h"
#include "Data/QPGIM_PlayerData.h"
#include "GamePlay/AttributeSet/QPAS_BaseBuff.h"
#include "Notify/QPGIM_AnimNotifyData.h"

// Sets default values


AQPCharacter::AQPCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
	qp_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	qp_springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	qp_springArm->bUsePawnControlRotation = true;
	qp_materialAutoRestore = CreateDefaultSubobject<UQPC_MaterialAutoRestore>("qp_materialAutoRestore");

	bUseControllerRotationYaw = false;
	qp_springArm->SetupAttachment(RootComponent);
	qp_camera->SetupAttachment(qp_springArm);
	
	//qp_attackAnim->SetupAttachment(RootComponent);
	//qp_restoreNg = CreateDefaultSubobject<UNiagaraComponent>("qp_restoreNg");
	//qp_restoreNg->SetupAttachment(RootComponent);
	//qp_aterialDissolve->QP_SetRootComponent(RootComponent);

	

	


}
void AQPCharacter::PreInitializeComponents() {
	Super::PreInitializeComponents();
	//if (UQPGIM_Character::qp_staticObject) 
	{

		//qp_assetData = UQPGIM_Character::qp_staticObject->QP_GetCharacterData(qp_assetDataName);

		
	}
}
//void AQPCharacter::OnConstruction(const FTransform& Transform) {
//	Super::OnConstruction(Transform);
//
//	if (UQPGIM_Data::qp_staticObject) {
//	}
//}
// Called when the game starts or when spawned
void AQPCharacter::BeginPlay()
{
	//UQPUtil::QP_LOG("_______________________dd_________________dd____________________");

	Super::BeginPlay();
	

	//QP_InitQPData();
	//if (qp_characterData == nullptr) {
		//qp_characterData = UQPGIM_Data::qp_staticObject->QP_GetQPData("AQPCharacter")->QP_GetUQPData("qp_Character" + qp_characterMaxNum);
	//}
	
	if (qp_assetData && !qp_assetData->qp_montage.IsEmpty()) {
		qp_playMontage->qp_montage.Append(qp_assetData->qp_montage);
	}
	qp_movementC->bOrientRotationToMovement = true;
	qp_movementC->MaxAcceleration = qp_walkMaxAcceleration;
	qp_movementC->bRunPhysicsWithNoController = true;
	qp_movementC->MaxWalkSpeed = qp_walkSpeed;
	qp_isFixedCamera = false;
	qp_isRun = false;
	qp_maxSpeed = qp_walkSpeed;
	//qp_characterData->QP_GetUQPData(UQPGIM_AnimNotifyData::QP_DATA_BASE_NAME)->qp_dataDelegate.AddUObject(this, &AQPCharacter::QP_AnimNotifyEvent);
	
	QP_AddLocalBuff();

	

	/*if (qp_isPlayer) {
		qp_springArm->SetVisibility(false, true);
	}
	else {
		qp_springArm->SetVisibility(true, true);
	}*/
	
	//qp_saveData->QP_AddFRotator("ControllerRotation", GetControlRotation());
	//qp_saveData->QP_Addfloat("TargetArmLength", qp_springArm->TargetArmLength);
	//UQPUtil::QP_LOG("_______________________dd_____________________________________");
}

// Called every frame
void AQPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	qp_deltaTime = DeltaTime;
	//UQPUtil::QP_LOG(GetControlRotation().ToString());

	if (qp_isAutoCameraLength) {
		
		if (qp_springArm->TargetArmLength>= qp_targetCameraLength) {
			QP_mouseWheelUp();
			if (qp_springArm->TargetArmLength <= qp_targetCameraLength) {
				qp_isAutoCameraLength = false;
			}
		}
		else if (qp_springArm->TargetArmLength <= qp_targetCameraLength) {
			QP_mouseWheelDown();
			if (qp_springArm->TargetArmLength >= qp_targetCameraLength) {
				qp_isAutoCameraLength = false;
			}
		}
		
		 
	}

	if (qp_movementC->IsFalling()) {
		if (qp_characterData->QP_GetFString("characterJump") != "start") {
			if (qp_characterData->QP_GetFString("characterFall") != "start") {
				qp_characterData->QP_AddFString("characterFall", "start");
				QP_PlayAnim("characterFall");
			}
		}
	}
	QP_UpdateMaxSpeed();
}

// Called to bind functionality to input
void AQPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	/*if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				
				
			}
		}
	}*/

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Input->BindAction()
	if (qp_jumpInputAction) {

		Input->BindAction(qp_jumpInputAction,ETriggerEvent::Started, this, &AQPCharacter::QP_JumpStart);
		Input->BindAction(qp_jumpInputAction, ETriggerEvent::Completed, this, &AQPCharacter::QP_JumpEnd);
	}
	if (qp_moveForwardInputAction) {

		Input->BindAction(qp_moveForwardInputAction, ETriggerEvent::Triggered, this, &AQPCharacter::QP_MoveForward);
	}
	if (qp_lookUPInputAction) {
		Input->BindAction(qp_lookUPInputAction, ETriggerEvent::Triggered, this, &AQPCharacter::QP_LookUP);
	}
	if (qp_moveRightInputAction) {

		Input->BindAction(qp_moveRightInputAction, ETriggerEvent::Triggered, this, &AQPCharacter::QP_MoveRight);
	}
	if (qp_TrunInputAction) {
		Input->BindAction(qp_TrunInputAction, ETriggerEvent::Triggered, this, &AQPCharacter::QP_TrunAxis);
	}
	if (qp_MoveUPInputAction) {

		Input->BindAction(qp_MoveUPInputAction, ETriggerEvent::Triggered, this, &AQPCharacter::QP_MoveUP);
	}
	//PlayerInputComponent->BindAxis(qp_moveForWard, this, &AQPCharacter::QP_MoveForward);
	//PlayerInputComponent->BindAxis(qp_turn, this, &AQPCharacter::QP_TrunAxis);


	//PlayerInputComponent->BindAxis(qp_mouseWhellAxis, this, &AQPCharacter::QP_MouseWheelAxis);

	if (qp_mouseLeftInputAction) {

		Input->BindAction(qp_mouseLeftInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_MouseLeftStart);
		Input->BindAction(qp_mouseLeftInputAction, ETriggerEvent::Completed, this, &AQPCharacter::QP_MouseLeftEnd);
	}

	if (qp_mouseRightInputAction) {

		Input->BindAction(qp_mouseRightInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_MouseRightStart);
		Input->BindAction(qp_mouseRightInputAction, ETriggerEvent::Completed, this, &AQPCharacter::QP_MouseRightEnd);
	}

	if (qp_runInputAction) {

		Input->BindAction(qp_runInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_Run);
	}
	if (qp_sneakInputAction) {

		Input->BindAction(qp_sneakInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_Sneak);
	}
	if (qp_fixedCameraInputAction) {

		Input->BindAction(qp_fixedCameraInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_FixedCamera);
	}
	if (qp_mouseWheelUpInputAction) {

		Input->BindAction(qp_mouseWheelUpInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_mouseWheelUp);
	}
	if (qp_mouseWheelDownInputAction) {

		Input->BindAction(qp_mouseWheelDownInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_mouseWheelDown);
	}
	if (qp_changeCharacterInputAction) {

		Input->BindAction(qp_changeCharacterInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_ChangeCharacter);
	}
	if (qp_switchMouseShowInputAction) {

		Input->BindAction(qp_switchMouseShowInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_SwitchMouseShow);
	}
	//PlayerInputComponent->BindAction(qp_run, IE_Pressed, this, &AQPCharacter::QP_Run);
	//PlayerInputComponent->BindAction(qp_sneak, IE_Released, this, &AQPCharacter::QP_Sneak);
	//PlayerInputComponent->BindAction(qp_attack, IE_Pressed, this, &AQPCharacter::QP_MouseLeftStart);
	//PlayerInputComponent->BindAction(qp_attack, IE_Released, this, &AQPCharacter::QP_MouseLeftEnd);
	//PlayerInputComponent->BindAction(qp_fixedCamera, IE_Pressed, this, &AQPCharacter::QP_FixedCamera);
	//PlayerInputComponent->BindAction(qp_attackTwo, IE_Pressed, this, &AQPCharacter::QP_AttackTwoStart);
	//PlayerInputComponent->BindAction(qp_attackTwo, IE_Released, this, &AQPCharacter::QP_AttackTwoEnd);
	//PlayerInputComponent->BindAction(qp_mouseWheelUp, IE_Pressed, this, &AQPCharacter::QP_mouseWheelUp);
	//PlayerInputComponent->BindAction(qp_mouseWheelDown, IE_Pressed, this, &AQPCharacter::QP_mouseWheelDown);
	//PlayerInputComponent->BindAction(qp_changeCharacter, IE_Pressed, this, &AQPCharacter::QP_ChangeCharacter);
	//PlayerInputComponent->BindAction(qp_switchMouseShow, IE_Pressed, this, &AQPCharacter::QP_SwitchMouseShow);

	/*if (GIsEditor)
	{
		if (qp_debugSwitchMouseShowInputAction) {

			Input->BindAction(qp_debugSwitchMouseShowInputAction, ETriggerEvent::Started, this, &AQPCharacter::QP_SwitchMouseShow);
		}
		*///PlayerInputComponent->BindAction("DebugSwitchMouseShow", IE_Pressed, this, &AQPCharacter::QP_SwitchMouseShow);
	//}
		
		
}
//void AQPCharacter::QP_InitQPData() {
//	
//	
//}
void AQPCharacter::QP_SwitchMouseShow() {
	UQPUtil::QP_SwitchMouseShow(Cast<APlayerController>(Controller));
}

void AQPCharacter::QP_SetMatAmount(float amount)
{
	//qp_matAmount = amount;
	//qp_matInstance->SetScalarParameterValue("qp_amount", qp_matAmount);
	qp_materialAutoRestore->QP_SetMatAmount(amount);
	

}

//virtual void QP_MouseWheelAxis(float value);
void AQPCharacter::QP_TrunAxis(const FInputActionValue& value) {
	AddControllerYawInput(value.Get<float>());
}
 void AQPCharacter::QP_LookUP(const FInputActionValue& value){
	 const FVector2D mv = value.Get<FVector2D>();

	 //AddControllerYawInput(mv.X);
	 AddControllerPitchInput(-value.Get<float>());
}
//void AQPCharacter::QP_MouseWheelAxis(float value)
//{
//	
//}
 /*void AQPCharacter::QP_InitSaveData() {
	 Super::QP_InitSaveData();
	 qp_saveData->QP_AddFRotator("ControllerRotation", GetControlRotation());
	 qp_saveData->QP_Addfloat("TargetArmLength", qp_springArm->TargetArmLength);
}
  void AQPCharacter::QP_ChangeSaveData() {
	  Super::QP_ChangeSaveData();
	  
 }*/
  void AQPCharacter::UnPossessed() {
	  
	  //UQPUtil::QP_LOG(GetControlRotation().ToString());
	  
	  if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		  if (PC->IsLocalPlayerController())
		  {
			  //if (qp_saveData) {
			  //UQPUtil::QP_LOG(GetControlRotation().ToString() + "_________________");
			  //UQPUtil::QP_LOG(GetActorTransform().ToString() + "_________________");
			  //UQPUtil::QP_LOG(GetControlRotation().ToString());
			  UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_AddFTransform("Transform", GetActorTransform());
			  UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Addfloat("TargetArmLength", qp_springArm->TargetArmLength);
			  
			  //}

			  
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				{
					//Subsystem->RemoveMappingContext(DefaultMappingContext);
					for (auto v : qp_inputMappingContext) {
						Subsystem->RemoveMappingContext(v);
					}
				}
			}


			if (qp_isAddLocalBuff) {

				if (const UAttributeSet* uset = qp_abilitySystemComponent->GetAttributeSet(UQPAS_BaseBuff::StaticClass())) {
					
					//UQPData* baseBuffData = UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetUQPData("slimeBaseBuffData");

					UQPData* baseBuffData_Add = QP_GetQPData()->QP_GetUQPData("baseBuffDataSet_Add");
					UQPData* baseBuffData = QP_GetQPData()->QP_GetUQPData("baseBuffDataSet");
					
					TMap<FName, FProperty*> t;
					for (TFieldIterator<FProperty> It(qp_assetData->GetClass()); It; ++It)
					{
						//Property = ;
						t.Add((*It)->GetFName(), (*It));
					}
					
					UClass* usetClass = uset->GetClass();
					UObject* DefaultObj = usetClass->GetDefaultObject();
					
					FProperty* Property;
					int DefaultValue = 0;
					float nowValue = 0;
					float num2 = 0;
					FStructProperty* StructProp;
					FName n;
					for (TFieldIterator<FProperty> It(usetClass); It; ++It)
					{
						Property = *It;
						StructProp = CastField<FStructProperty>(Property);
						if (StructProp)
						{
							if (StructProp->Struct == TBaseStructure<FGameplayAttributeData>::Get())
							{
								DefaultValue = (static_cast<FGameplayAttributeData*>(StructProp->ContainerPtrToValuePtr<void>(DefaultObj)))->GetBaseValue();
								nowValue = (static_cast<const FGameplayAttributeData*>(StructProp->ContainerPtrToValuePtr<void>(uset)))->GetBaseValue();
								n = Property->GetFName();
								if (DefaultValue & (uint16)EQPBaseBuffDataType::LocalData_Add) {
									
									num2 = 0;
									if (t.Contains(n)) {
										if (FFloatProperty* FloatProp = CastField<FFloatProperty>(t[n]))
										{
											num2 = FloatProp->GetPropertyValue_InContainer(qp_assetData);
										}
									}
									else {
										UQPUtil::QP_LOG("not qp_assetData name " + n.ToString());
									}

									baseBuffData_Add->QP_Addfloat(n, nowValue - num2);
								}
								else if (DefaultValue & (uint16)EQPBaseBuffDataType::LocalData) {
									baseBuffData->QP_Addfloat(n, nowValue);
								}
							
							}
							
						}
						

						//UE_LOG(LogTemp, Log, TEXT("____%s"), *Property->GetFName().ToString());
					}
					baseBuffData_Add->QP_SaveDataFAES("baseBuffDataSet_Add" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_Add_A" + qp_assetData->qp_name.ToString())));
					baseBuffData->QP_SaveDataFAES("baseBuffDataSet" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_A" + qp_assetData->qp_name.ToString())));
				}
			}
		  }
	  }
	  Super::UnPossessed();

  }
  void AQPCharacter::PossessedBy(AController* NewController) {
	 
	  Super::PossessedBy(NewController);
	 

	  if (APlayerController* PC = Cast<APlayerController>(NewController))
	  {

		  if (PC->IsLocalPlayerController())
		  {
			  if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			  {
				  if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				  {
					  int index = 0;
					  for (auto v : qp_inputMappingContext) {
						  Subsystem->AddMappingContext(v, index);
						  index++;
					  }
					  /*Subsystem->AddMappingContext(DefaultMappingContext, 0);*/
				  }
			   }
				if (UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getbool("qp_autoTransform")) 
				{
					SetActorTransform(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFTransform("Transform"));
				}
				if (UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getbool("qp_autoTargetArmLength"))
				{
					qp_springArm->TargetArmLength = UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Getfloat("TargetArmLength");
				}
				UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Addbool("qp_autoTargetArmLength", true);
				UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Addbool("qp_autoTransform", true);
				//UQPUtil::QP_LOG(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFTransform("Transform").ToString() + "_________________");
				//UQPUtil::QP_LOG(UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetFRotator("ControllerRotation").ToString() + "_________________");

				


			  
		   }
	   }
	  QP_AddLocalBuff();
	 
  }
  void AQPCharacter::QP_AddLocalBuff() {
	  if (!qp_isAddLocalBuff) {
		  const UAttributeSet* uset = qp_abilitySystemComponent->GetAttributeSet(UQPAS_BaseBuff::StaticClass());
		  if ((Controller && Controller->IsLocalPlayerController()&& uset)||(qp_forceAddLocalBuff&& uset)) {
			  qp_isAddLocalBuff = true;
			  //UQPData* baseBuffData = UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_GetUQPData("slimeBaseBuffData");
			  //UE_LOG(LogTemp, Log, TEXT("____%s"), *qp_assetData->qp_name.ToString());
			  UQPData* baseBuffData_Add = QP_GetQPData()->QP_GetUQPData("baseBuffDataSet_Add");
			  baseBuffData_Add->QP_LoadDataFAES("baseBuffDataSet_Add" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_Add_A" + qp_assetData->qp_name.ToString())));
			  
			  UQPData* baseBuffData = QP_GetQPData()->QP_GetUQPData("baseBuffDataSet");
			  baseBuffData->QP_LoadDataFAES("baseBuffDataSet" + qp_assetData->qp_name.ToString(), UQPGIM_BaseData::qp_staticObject->GetAESKey(FName("baseBuffDataSet_A" + qp_assetData->qp_name.ToString())));
			  if (baseBuffData->QP_Getbool("qp_isinit")) {


				  //-----------------------------
				  UClass* usetClass = uset->GetClass();
				  UObject* DefaultObj = usetClass->GetDefaultObject();

				  FProperty* Property;
				  int DefaultValue = 0;
				  float num2 = 0;
				  FName n;

				  FGameplayAttributeData* nowD;
				  FStructProperty* StructProp;
				  for (TFieldIterator<FProperty> It(usetClass); It; ++It)
				  {


					  Property = *It;
					  StructProp = CastField<FStructProperty>(Property);

					  if (StructProp)
					  {
						  if (StructProp->Struct == TBaseStructure<FGameplayAttributeData>::Get())
						  {

							  DefaultValue = (static_cast<FGameplayAttributeData*>(StructProp->ContainerPtrToValuePtr<void>(DefaultObj)))->GetBaseValue();
							  nowD = (FGameplayAttributeData*)(StructProp->ContainerPtrToValuePtr<void>(uset));
							  n = Property->GetFName();
							  if (DefaultValue & (uint16)EQPBaseBuffDataType::LocalData_Add) {

								  //FGameplayAttribute p(Property);
								  //float num =;
								  nowD->SetBaseValue(nowD->GetBaseValue() + baseBuffData_Add->QP_Getfloat(n));
								  nowD->SetCurrentValue(nowD->GetBaseValue());
								  //qp_abilitySystemComponent->SetNumericAttributeBase(p, );
							  }
							  else if (DefaultValue & (uint16)EQPBaseBuffDataType::LocalData) {
								  //qp_abilitySystemComponent->SetNumericAttributeBase(FGameplayAttribute(Property), baseBuffData->QP_Getfloat(n));
								  nowD->SetBaseValue(baseBuffData->QP_Getfloat(n));
									nowD->SetCurrentValue(nowD->GetBaseValue());
							  }
						  } 
					  }
					  
				  }
			  }
			  baseBuffData->QP_Addbool("qp_isinit", true);

				
		  }
	  }
  }
  void AQPCharacter::QP_MoveUP(const FInputActionValue& value) {
	  if (qp_movementC->MovementMode == MOVE_Flying || qp_movementC->MovementMode == MOVE_Swimming) {
		 
		  //AddMovementInput(GetControlRotation().Vector(), value.Get<float>());
		  //qp_movementC->bOrientRotationToMovement = false;
		  FRotator yawRotation = GetControlRotation();
		  FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Z);
		  AddMovementInput(rightVector, value.Get<float>());
	  }
	  else {
		  FRotator yawRotation(0, GetControlRotation().Yaw, 0);
		  FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Z);
		  AddMovementInput(rightVector, value.Get<float>());
	  }
	  
	  ;
	  //FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	  //FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	  //AddMovementInput(yawRotation.Vector(), value.Get<float>());

	  //qp_movementC->bOrientRotationToMovement = !qp_isFixedCamera;
  }
void AQPCharacter::QP_MoveForward(const FInputActionValue& value)
{
	//const FVector2D mv = value.Get<FVector2D>();
	//FRotator yawRotation = GetControlRotation();
	if (qp_movementC->MovementMode == MOVE_Flying || qp_movementC->MovementMode == MOVE_Swimming) {
		FRotator yawRotation= GetControlRotation();
		FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(rightVector, value.Get<float>());
		//AddMovementInput(GetControlRotation().Vector(), value.Get<float>());
	}
	else {
		//FRotator yawRotation(0, GetControlRotation().Yaw, 0);
		
		FRotator yawRotation(0, GetControlRotation().Yaw, 0);
		FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(rightVector, value.Get<float>());
	}
	//FRotator yawRotation(0, GetControlRotation().Yaw,0);
	;
	//FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	//FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	
	//AddMovementInput(rightVector, mv.X);

	/* qp_forwardV = value;
	if (value != 0) {
		
		FRotator rotator = GetControlRotation();
		rotator.Roll = 0.0f;
		rotator.Pitch = 0.0f;

		AddMovementInput(rotator.Vector(), value);

	}*/

	// animInst->PlaySlotAnimation(animSequence,"Slime_Anim_Armature_ForwardMove");
}

void AQPCharacter::QP_MoveRight(const FInputActionValue& value)
{

	//FRotator yawRotation(0, GetControlRotation().Yaw, 0);
	//FRotator yawRotation = GetControlRotation();
	if (qp_movementC->MovementMode == MOVE_Flying || qp_movementC->MovementMode == MOVE_Swimming) {
		
		//AddMovementInput(GetControlRotation().Vector(), value.Get<float>());
		FRotator yawRotation = GetControlRotation();
		FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(rightVector, value.Get<float>());
	}
	else {
		FRotator yawRotation(0, GetControlRotation().Yaw, 0);
		FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(rightVector, value.Get<float>());
	}
	//FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	
	/*qp_rightV = value;
	if (value != 0) {
		
		FRotator rotator = GetControlRotation();
		rotator.Roll = 0.0f;
		rotator.Pitch = 0.0f;

		FVector rightVector = FRotationMatrix(rotator).GetScaledAxis(EAxis::Y);
		AddMovementInput(rightVector, value);
	}*/
}

//前行的切换
void AQPCharacter::QP_Sneak() {
	qp_isRun = !qp_isRun;
	if (qp_isRun) {
		QP_SneakStart();
	}
	else {
		QP_SneakEnd();
	}
}
void AQPCharacter::QP_SneakStart(){
	qp_maxSpeed = qp_sneakSpeed;
	qp_movementC->MaxAcceleration = qp_sneakMaxAcceleration;
}
void AQPCharacter::QP_SneakEnd(){
	qp_maxSpeed = qp_walkSpeed;
	qp_movementC->MaxAcceleration = qp_walkMaxAcceleration;
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
	 //qp_movementC->MaxWalkSpeed = qp_maxSpeed;

 }
 void AQPCharacter::QP_RunEnd()
 {
	 qp_maxSpeed = qp_walkSpeed;
	 qp_movementC->MaxAcceleration = qp_walkMaxAcceleration;
	 //qp_movementC->MaxWalkSpeed = qp_maxSpeed;


 }
 //脱离玩家控制时调用
 void AQPCharacter::QP_PlayerExit() {
	 qp_movementMode = qp_movementC->MovementMode;

	 qp_isExit = true;
	 QP_Reset();
	 
 }
 //进入玩家控制时调用
 void AQPCharacter::QP_PlayerEnter() {
	 if (!qp_isExit) {
		 return;
	 }
	 qp_isExit = false;
	 QP_ReReset();
 }
 void AQPCharacter::QP_Reset() {
	 qp_isReset = true;
	 qp_isFixedCameraLast = qp_isFixedCamera;
	 qp_isRunLast = qp_isRun;
	 if (qp_isFixedCamera) {
		 QP_FixedCamera();
	 }
	 if (qp_isRun) {
		 QP_Run();
	 }
	 if (qp_characterData->QP_GetFString("characterAttack") == "start") {
		 QP_MouseLeftEnd();
	 }
 }
void AQPCharacter::QP_ReReset() {
	if (!qp_isReset) {
		return;
	}
	qp_isReset = false;

	if (qp_isFixedCameraLast) {
		QP_FixedCamera();
	}
	if (qp_isRunLast) {
		QP_Run();
	}
	qp_isFixedCameraLast = false;
	qp_isRunLast = false;
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
 void AQPCharacter::QP_MouseRightStart()
 {
 }
//松开鼠标右键
 void AQPCharacter::QP_MouseRightEnd()
 {
 }

 void AQPCharacter::QP_JumpStart()
 {
	 //如果是真的话，角色跳跃
	 Jump();
	 //bPressedJump = true;
	 qp_characterData->QP_AddFString("characterJump", "start");
	 QP_PlayAnim("characterJump");

 }
 void AQPCharacter::QP_JumpEnd()
 {
	 StopJumping();
	 //bPressedJump = false;
	 //GLog->Log("jumpEnd");

 }

 void AQPCharacter::Landed(const FHitResult& Hit) {
	 Super::Landed(Hit);
	 qp_characterData->QP_AddFString("characterJump", "end");
	 //qp_characterData->QP_AddFString("characterFall", "notPlay");
	 QP_PlayAnim("characterJump", "end");


 }


 void AQPCharacter::QP_MouseLeftStart()
 {
	 qp_characterData->QP_AddFString("characterAttack", "start");
	 QP_PlayAnim("characterAttack");

	 qp_isAttacking = true;
 }

 void AQPCharacter::QP_MouseLeftEnd()
 {
	 qp_characterData->QP_AddFString("characterAttack", "end");
	 QP_PlayAnim("characterAttack", "end");
	 
	 
	 qp_isAttacking = false;
 }

 void AQPCharacter::QP_ChangeCharacter()
 {
	 //qp_isFixedCameraLast = qp_isFixedCamera;

	 //QP_Reset();
	 //AutoPossessPlayer = EAutoReceiveInput::Type::Disabled;

	 //UQPGIM_Character::qp_staticObject->QP_GetCharacter("FlySlime")->AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
	 UQPGIM_PlayerData::qp_staticObject->QP_GetLocalPlayerSaveData()->QP_Addbool("qp_autoTransform", false);
	 UQPGIM_Character::qp_staticObject->QP_Possess(GetController(), qp_changeCharacterName, qp_unchangeMovementMode);
	 //->Possess(QP_GetCharacter());
 //GetController()->Possess(UQPGIM_Character::qp_staticObject->QP_GetCharacter("FlySlime"));
 //GetController()->SetPawn(UQPGIM_Character::qp_staticObject->QP_GetCharacter("FlySlime"));
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
	 else {
		 qp_isAutoCameraLength = false;

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
	 else {
		 qp_isAutoCameraLength = false;

	 }
 }

 //void AQPCharacter::QP_AnimNotify(const FName& n) {
	// //GLog->Log("QP_AnimNotifyFire");
	//
	//
	// 
 //}

 //void AQPCharacter::QP_Fire() {
	// 
 //}

  void AQPCharacter::QP_PlayerDataChange(UQPData* data) {
	  Super::QP_PlayerDataChange(data);

	  //if (data->QP_IsChange<FName, UObject>("showInformationObj", EQPDataValueType::UOBJECT)) {
		 // qp_camera->HiddenActors;
		 // //qp_isMouseMove = data->QP_Getbool("mouseMove");
	  //}

	  //if (APlayerController* PC = Cast<APlayerController>(GetController())) 
	  //{
		 // if (PC->IsLocalPlayerController())
		 // {

		 // }
	  //}
 }