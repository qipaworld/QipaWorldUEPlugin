// QIPAWORLD


#include "Monster/QPMonster.h"
#include "Data/QPGIM_Data.h"
#include "UObject/UnrealType.h"
#include "Data/QPData.h"
int AQPMonster::qp_characterDataMaxNum = 1;
// Sets default values
AQPMonster::AQPMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AQPMonster::BeginPlay()
{
	Super::BeginPlay();
	QP_GetAnimData();
	//QP_GetQPData();
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
void AQPMonster::QP_AnimNotify(const FName& k) {

}
UQPData* AQPMonster::QP_GetAnimData() {

	if (!qp_animData) {
		qp_animData = QP_GetQPData()->QP_GetUQPData("qp_AnimData");

	}
	return qp_animData;
}
void AQPMonster::QP_PlayAnim(FName name, FName StartSectionName) {
	qp_animData->QP_AddFName("playAnim", name);
	qp_animData->QP_AddFName("startSectionName", StartSectionName);
}