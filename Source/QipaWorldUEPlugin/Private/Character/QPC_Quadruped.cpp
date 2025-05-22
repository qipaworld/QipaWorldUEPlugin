// QIPAWORLD


#include "Character/QPC_Quadruped.h"


#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

//qp_assetDataName = "FlySlime";
void AQPC_Quadruped::QP_RestorSlime() {
	UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Addfloat("flyCameraLength", qp_springArm->TargetArmLength);

}

void AQPC_Quadruped::QP_AnimNotify(const FName& n) {
	Super::QP_AnimNotify(n);
	
		if (n == "qp_flySlimeReduceEnd") {
			qp_targetCameraLength = qp_springArm->TargetArmLength;
			qp_springArm->TargetArmLength = UQPGIM_BaseData::qp_staticObject->QP_GetPlayerData()->QP_Getfloat("flyCameraLength");
			qp_isAutoCameraLength = true;
			QP_SetMatAmount();
		}
	
	
 }


/**创建魔法技能*/
void AQPC_Quadruped::QP_Fire() {
	Super::QP_Fire();

	//GLog->Log("QP_Fire");
	//GetMesh()->GetSocketByName()->ro
	FVector location = GetMesh()->GetSocketLocation("top_attack");
	FRotator rotetion = GetMesh()->GetSocketRotation("top_attackRotator");
	FTransform qp_spawnT = FTransform(rotetion, location);
	//FTransform qp_spawnT = FTransform(GetActorRotation(), location);
	FActorSpawnParameters qp_spawnP;
	qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//qp_attackSkill->
	//float qp_skillSpeed = qp_attackSkill.QP_GetMovement()->InitialSpeed;
	//qp_attackSkill->QP_GetMovement()->InitialSpeed = qp_skillSpeed + GetCharacterMovement()->GetLastUpdateVelocity()->Size();

	AQPS_CollisionMovement* qp_skill = GetWorld()->SpawnActor<AQPS_CollisionMovement>(qp_attackSkill, qp_spawnT, qp_spawnP);
	//qp_skill->QP_GetMovement()->InitialSpeed = 2000;
	//GLog->Log();
	//UE_LOG(LogTemp, Log, TEXT("Actor location: %s"), *GetCharacterMovement()->GetLastUpdateVelocity().ToString());


	qp_skill->QP_AddMoveVelocity(GetCharacterMovement()->GetLastUpdateVelocity());

}

	//按下鼠标右键
void AQPC_Quadruped::QP_AttackTwoStart() {

}
	//松开鼠标右键
void AQPC_Quadruped::QP_AttackTwoEnd() {
	QP_RestorSlime();
}