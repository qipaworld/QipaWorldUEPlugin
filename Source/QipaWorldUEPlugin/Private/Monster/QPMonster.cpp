// QIPAWORLD


#include "Monster/QPMonster.h"
#include "Data/QPGIM_Data.h"
#include "UObject/UnrealType.h"

#include "Components/CapsuleComponent.h"
#include "Data/QPData.h"
int AQPMonster::qp_characterDataMaxNum = 1;
// Sets default values
AQPMonster::AQPMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UQPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	qp_footstepAudio = CreateDefaultSubobject<UAudioComponent>("footstepAudio");
	qp_footstepAudio->SetAutoActivate(false);
	qp_footstepAudio->SetupAttachment(RootComponent);


	qp_callAudio = CreateDefaultSubobject<UAudioComponent>("qp_callAudio");
	qp_callAudio->SetAutoActivate(false);
	qp_callAudio->SetupAttachment(RootComponent);

	qp_deepWaterPoint = CreateDefaultSubobject<USceneComponent>("qp_deepWaterPoint");
	qp_deepWaterPoint->SetupAttachment(RootComponent);

	qp_underWaterPoint = CreateDefaultSubobject<USceneComponent>("qp_underWaterPoint");
	qp_underWaterPoint->SetupAttachment(RootComponent);

	qp_playRandomSound = CreateDefaultSubobject<UQPC_PlayRandomSound>("qp_playRandomSound");
	//qp_playRandomSound->qp_footstepAudio = qp_footstepAudio;
	//qp_playRandomSound->SetupAttachment(RootComponent);
	qp_sphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("qp_sphereTrigger"));
	qp_sphereTrigger->SetupAttachment(RootComponent);
	qp_playMontage = CreateDefaultSubobject<UQPC_PlayMontage>("qp_playMontage");

	qp_abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("qp_abilitySystem"));

	//qp_stateTree = CreateDefaultSubobject<UStateTreeComponent>(TEXT("qp_stateTree"));
	//qp_stateTree->setlo = false;
	//qp_stateTree->SetStartLogicAutomatically(false);


}

// Called when the game starts or when spawned
void AQPMonster::BeginPlay()
{
	Super::BeginPlay();

	qp_animInst = Cast<UQPU_AnimInstance>(GetMesh()->GetAnimInstance());
	if (qp_animInst) {
		qp_animInst->QP_SetQPData(QP_GetQPData());
	}
	if (!qp_montage.IsEmpty()) {
		qp_playMontage->qp_montage.Append(qp_montage);
	}
	qp_movementC = (UQPCharacterMovementComponent*) GetCharacterMovement();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AQPMonster::QP_OnCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AQPMonster::QP_OnCapsuleEndOverlap);
	qp_sphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AQPMonster::QP_OnTriggerOverlapBegin);
	qp_sphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AQPMonster::QP_OnTriggerOverlapEnd);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AQPMonster::QP_OnCapsuleHit);

	QP_GetAnimData();

	if (!qp_saveName.IsEmpty()) {
		QP_GetSaveData()->QP_LoadData(qp_saveName);
		if (!qp_saveData->QP_Getbool("qp_init")) {
			QP_InitSaveData();
		}
	}

	qp_playCallTime = FMath::FRandRange(qp_playCallTimeMin, qp_playCallTimeMax);
	/*if (qp_AutoPlayStateTree) {
		qp_stateTree->StartLogic();
	}*/
	QP_GetQPData()->qp_dataDelegate.AddUObject(this, &AQPMonster::QP_DataChange);
	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->qp_dataDelegate.AddUObject(this, &AQPMonster::QP_PlayerDataChange);


	for (TSubclassOf<UAttributeSet> SetClass : qp_preloadedAttributeSet)
	{
		if (SetClass)
		{
			// ���� AttributeSet ʵ������ע�ᵽ AbilitySystem
			UAttributeSet* NewSet = NewObject<UAttributeSet>(qp_abilitySystemComponent, SetClass);
			qp_abilitySystemComponent->AddAttributeSetSubobject(NewSet);
		}
	}

	if (qp_abilitySystemComponent != nullptr)
	{
		//��ʼ������
		if (qp_preloadedAbilities.Num() > 0)
		{
			for (auto i = 0; i < qp_preloadedAbilities.Num(); i++)
			{
				if (qp_preloadedAbilities[i] != nullptr)
				{

					qp_abilitySystemComponent->GiveAbility(
						FGameplayAbilitySpec(qp_preloadedAbilities[i].GetDefaultObject(), 1));
				}
			}
		}

		//��ʼ��ASC
		qp_abilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
void AQPMonster::QP_PlayerDataChange(UQPData* data) {

}
void AQPMonster::QP_SetSaveDataName(const FString& n) {
	qp_saveName = n;
	this->QP_GetSaveData()->QP_LoadData(qp_saveName);
}
void AQPMonster::QP_OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UQPUtil::QP_LOG("Hit");
	//Destroy();
}

void AQPMonster::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (!qp_saveName.IsEmpty()) {
		QP_ChangeSaveData();
		QP_GetSaveData()->QP_SaveData(qp_saveName);
	}
	Super::EndPlay(EndPlayReason);
}
 void AQPMonster::QP_OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	 if (OtherActor->Tags.Contains("water")) {
		 qp_waters.Add(OtherActor);
		 
		 
		 
	 }
	 //UE_LOG(LogTemp, Warning, TEXT("Capsule overlapped with %s"), *OtherActor->GetName());

}
 void AQPMonster::QP_OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	 //UE_LOG(LogTemp, Warning, TEXT("Capsule overlapped with %s"), *OtherActor->GetName());
	 if (OtherActor->Tags.Contains("water")) {
		 qp_waters.Remove(OtherActor);
	 }
 }

 void AQPMonster::QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
	 //if ("BP_ChaosJar_116" == GetActorLabel())
		 //UE_LOG(LogTemp, Warning, TEXT("___!__d_d___%s"), *OtherActor->GetActorLabel());
	 
 }

 void AQPMonster::QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
	 //if ("BP_ChaosJar_116" == GetActorLabel())
		 //UE_LOG(LogTemp, Warning, TEXT("___!___d___%s"), *OtherActor->GetActorLabel());
 }
 void AQPMonster::QP_PlayCall() {

 }
void AQPMonster::QP_ChangeSaveData() {

}
void AQPMonster::QP_InitSaveData() {
	qp_saveData->QP_Addbool("qp_init", true);
}

// Called every frame
void AQPMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (qp_isPlayCall) {
		qp_playCallTime -= DeltaTime;
		if (qp_playCallTime <= 0) {
			QP_PlayCall();
			qp_playCallTime = FMath::FRandRange(qp_playCallTimeMin, qp_playCallTimeMax);

		}
	}
}

// Called to bind functionality to input
void AQPMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
 UQPData* AQPMonster::QP_GetQPData_BP()
 { 
	 return QP_GetQPData(); 
 }
UQPData* AQPMonster::QP_GetQPData() {

	if (!qp_characterData) {
		qp_characterDataMaxNum++;
		
		qp_characterData = UQPGIM_Data::qp_staticObject->QP_GetUQPData("AQPCharacter")->QP_GetUQPData(*FString::Printf(TEXT("qp_Character%d"), qp_characterDataMaxNum));

	}
	return qp_characterData;
}
void AQPMonster::QPI_AnimNotifyFootstep(EQPFootstepType t, const FHitResult& v, float minVolume) {
	//if (k == QP_AnimNotifyFootsetpAudio) {
		if (qp_isPlayFootstepAudio) {
			if (qp_waters.Num()> 0) {
				if (qp_waters.Last()->GetActorLocation().Z > qp_underWaterPoint->GetComponentLocation().Z && qp_playRandomSound->qp_randomSounds.Contains(EQPFootstepType::UNDER_WATER)) {
					t = EQPFootstepType::UNDER_WATER;
				}
				else if (qp_waters.Last()->GetActorLocation().Z > qp_deepWaterPoint->GetComponentLocation().Z && qp_playRandomSound->qp_randomSounds.Contains(EQPFootstepType::DEEP_WATER)) {
					t = EQPFootstepType::DEEP_WATER;
				}
				else {
					t = EQPFootstepType::WATER;

				}

				//t = qp_waterFootstep;
				//UE_LOG(LogTemp, Warning, TEXT("Hit Actor:______"));
			}
			if (!qp_playRandomSound->qp_randomSounds.Contains(t)) {
				t = EQPFootstepType::DEFAULT;
			}
			qp_footstepAudio->SetVolumeMultiplier(qp_movementC->Velocity.Size() / qp_runSpeed * (1 - minVolume) + minVolume);
			qp_playRandomSound->QP_Play(t, qp_footstepAudio);
			/*if (t == EQPFootstepType::DEFAULT) {
			} else if (t == EQPFootstepType::WOOD) {
				qp_footstepAudio->SetIntParameter("qp_type", 1);
			}
			else if (t == EQPFootstepType::TILE) {
				qp_footstepAudio->SetIntParameter("qp_type", 2);
			}
			else if (t == EQPFootstepType::WOOD2) {
				qp_footstepAudio->SetIntParameter("qp_type", 6);
			}*/
			//qp_footstepAudio->SetWaveParameter
		 //UE_LOG(LogTemp, Warning, TEXT("Hit Actor:______"));
			// 
			
			//qp_movementC->speed
			
		}
	//}
}
//void AQPMonster::QP_PlayHitSound(AActor* a) {
	

//}
 void AQPMonster::QP_PlayFootstepAudio() {

	 //FVector Start = GetActorLocation(); // �������
	 //FVector ForwardVector = GetActorForwardVector(); // ����
	 //FVector End = Start + (ForwardVector * 1000.0f); // �����յ㣨���� 1000��

	 //FHitResult HitResult;
	 //FCollisionQueryParams Params;
	 //Params.AddIgnoredActor(this); // �����Լ�

	 //bool bHit = GetWorld()->LineTraceSingleByChannel(
		// HitResult,
		// Start,
		// End,
		// ECC_Visibility, // �� ECC_GameTraceChannel1 �Զ�����ײͨ��
		// Params
	 //);

	 //if (bHit)
	 //{
		// UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
	 //}

	 
}
void AQPMonster::QPI_AnimNotify(const FName& k) {

	
	if (k == QP_AnimNotifyFireName) {
		QP_Fire();
	}
	else if (k == QP_AnimNotifyJunmEndName) {
		if (qp_characterData->QP_GetFString("characterAttack") == "start") {
			//qp_characterData->QP_AddFString("characterAttack", "start");
			QP_PlayAnim("characterAttack");

		}
	}
	
}
void AQPMonster::QP_Fire() {
   // 
}
UQPData* AQPMonster::QP_GetAnimData() {

	if (!qp_animData) {
		qp_animData = QP_GetQPData()->QP_GetUQPData("qp_animData");

	}
	return qp_animData;
}
UQPData* AQPMonster::QP_GetSaveData() {
	if (!qp_saveData) {
		qp_saveData = QP_GetQPData()->QP_GetUQPData("qp_saveData");

	}
	return qp_saveData;
}
void AQPMonster::QP_PlayAnim(FName name, FName StartSectionName) {
	qp_animData->QP_AddFName("playAnim", name);
	qp_animData->QP_AddFName("startSectionName", StartSectionName);
}
void AQPMonster::QP_DataChange(UQPData* data) {

}

UAbilitySystemComponent* AQPMonster::GetAbilitySystemComponent()const
{ 
	return qp_abilitySystemComponent;
}
