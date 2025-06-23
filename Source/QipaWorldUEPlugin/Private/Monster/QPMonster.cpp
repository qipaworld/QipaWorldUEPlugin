// QIPAWORLD


#include "Monster/QPMonster.h"
#include "Data/QPGIM_Data.h"
#include "UObject/UnrealType.h"

#include "Components/CapsuleComponent.h"
#include "Data/QPData.h"
int AQPMonster::qp_characterDataMaxNum = 1;
// Sets default values
AQPMonster::AQPMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	qp_footstepAudio = CreateDefaultSubobject<UAudioComponent>("footstepAudio");
	qp_footstepAudio->SetAutoActivate(false);
	qp_footstepAudio->SetupAttachment(RootComponent);

	qp_deepWaterPoint = CreateDefaultSubobject<USceneComponent>("qp_deepWaterPoint");
	qp_deepWaterPoint->SetupAttachment(RootComponent);

	qp_underWaterPoint = CreateDefaultSubobject<USceneComponent>("qp_underWaterPoint");
	qp_underWaterPoint->SetupAttachment(RootComponent);

	qp_playRandomSound = CreateDefaultSubobject<UQPC_PlayRandomSound>("qp_playRandomSound");
	qp_playRandomSound->qp_footstepAudio = qp_footstepAudio;
	//qp_playRandomSound->SetupAttachment(RootComponent);

	

}

// Called when the game starts or when spawned
void AQPMonster::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AQPMonster::QP_OnCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AQPMonster::QP_OnCapsuleEndOverlap);
	QP_GetAnimData();
	QP_InitSaveData();
	if (!qp_saveName.IsEmpty()) {
		qp_saveData->QP_LoadData(qp_saveName);
	}
	//QP_GetQPData();
}
void AQPMonster::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	if (!qp_saveName.IsEmpty()) {
		QP_ChangeSaveData();
		qp_saveData->QP_SaveData(qp_saveName);
	}
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

void AQPMonster::QP_ChangeSaveData() {

}
// Called every frame
void AQPMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQPMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UQPData* AQPMonster::QP_GetQPData() {

	if (!qp_characterData) {
		qp_characterDataMaxNum++;
		
		qp_characterData = UQPGIM_Data::qp_staticObject->QP_GetUQPData("AQPCharacter")->QP_GetUQPData(*FString::Printf(TEXT("qp_Character%d"), qp_characterDataMaxNum));

	}
	return qp_characterData;
}
void AQPMonster::QPI_AnimNotifyFootstep(EQPFootstepType t, FVector v, float minVolume) {
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
			qp_playRandomSound->QP_SetVolume(qp_movementC->Velocity.Size() / qp_runSpeed * (1 - minVolume) + minVolume);
			qp_playRandomSound->QP_Play(t);
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
 void AQPMonster::QP_PlayFootstepAudio() {

	 //FVector Start = GetActorLocation(); // 射线起点
	 //FVector ForwardVector = GetActorForwardVector(); // 方向
	 //FVector End = Start + (ForwardVector * 1000.0f); // 射线终点（长度 1000）

	 //FHitResult HitResult;
	 //FCollisionQueryParams Params;
	 //Params.AddIgnoredActor(this); // 忽略自己

	 //bool bHit = GetWorld()->LineTraceSingleByChannel(
		// HitResult,
		// Start,
		// End,
		// ECC_Visibility, // 或 ECC_GameTraceChannel1 自定义碰撞通道
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
void AQPMonster::QP_InitSaveData() {
	if (!qp_saveData) {
		qp_saveData = QP_GetQPData()->QP_GetUQPData("qp_saveData");

	}
}
void AQPMonster::QP_PlayAnim(FName name, FName StartSectionName) {
	qp_animData->QP_AddFName("playAnim", name);
	qp_animData->QP_AddFName("startSectionName", StartSectionName);
}