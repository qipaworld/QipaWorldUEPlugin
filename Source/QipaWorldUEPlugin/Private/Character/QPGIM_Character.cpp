// QIPAWORLD


#include "Character/QPGIM_Character.h"
#include "Animation/QPC_PlayMontage.h"

#include "Actor/QPWM_Actor.h"
#include "Character/QPDA_Character.h"

UQPGIM_Character* UQPGIM_Character::qp_staticObject = nullptr;


bool UQPGIM_Character::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Character::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	qp_staticObject = this;


	//QP_LoadSoundData();

	//qp_loadMapName = UQPDS_Default::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Character::Deinitialize()
{
	//if (qp_bgSound != nullptr) {
		//qp_bgSound->Stop();
	//}
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
//	QP_SaveSoundData();
	Super::Deinitialize();
	qp_staticObject = nullptr;

}
void UQPGIM_Character::QP_AddCharacter(FString qp_name, ACharacter* c) {
	qp_characterMap.Add(qp_name, c);
}
void UQPGIM_Character::QP_Possess(AController* controller, FString qp_name, bool qp_unchangeMovementMode, bool qp_isEnter, bool qp_isEixt) {
	if (qp_isEixt) {
		Cast<AQPCharacter>(controller->GetCharacter())->QP_PlayerExit();
	}
	AQPCharacter* c = Cast<AQPCharacter>(QP_GetCharacter(qp_name));
	controller->Possess(c);
	if (qp_isEnter) {
		c->QP_PlayerEnter();
	}
	if (qp_unchangeMovementMode) {
		c->GetCharacterMovement()->SetMovementMode(c->qp_movementMode);
	}
}
ACharacter* UQPGIM_Character::QP_GetCharacter(FString qp_name) {
	if (qp_characterMap.Contains(qp_name))
	{
		return qp_characterMap[qp_name];
	}
	return nullptr;
}
class UQPDA_Character* UQPGIM_Character::QP_GetCharacterData(FString qp_name) {
	return LoadObject<UQPDA_Character>(nullptr, *(qp_assetPath + qp_name + "." + qp_name + "'"));
}
void UQPGIM_Character::QP_InitCharacterData(AQPCharacter* c) {
	UQPDA_Character* data = QP_GetCharacterData(c->qp_assetDataName);
	c->qp_assetData = data;
	c->qp_playMontage->qp_montage.Append(data->qp_montage);
}
ACharacter* UQPGIM_Character::QP_GetNewCharacter(FString qp_name, FTransform T) {
	AActor* a = UQPWM_Actor::qp_staticObject->QP_GetActor(qp_name);
	ACharacter* c;
	if (!a) {
		//qp_character
		UQPDA_Character* data = QP_GetCharacterData(qp_name);
	
		//FTransform qp_spawnT = FTransform(GetActorRotation(), location);
		FActorSpawnParameters qp_spawnP;
		qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//qp_attackSkill->
		//float qp_skillSpeed = qp_attackSkill.QP_GetMovement()->InitialSpeed;
		//qp_attackSkill->QP_GetMovement()->InitialSpeed = qp_skillSpeed + GetCharacterMovement()->GetLastUpdateVelocity()->Size();
		
		c = GetWorld()->SpawnActor<ACharacter>(data->qp_character, T, qp_spawnP);
		AQPCharacter* qpc = Cast<AQPCharacter>(c);
		if (qpc) {
			QP_InitCharacterData(qpc);
		}
		else {
			UQPC_PlayMontage* pm = Cast<UQPC_PlayMontage>(c->GetComponentByClass(UQPC_PlayMontage::StaticClass()));

			if (pm) {
				pm->qp_montage.Append(data->qp_montage);
			}
		}
		
		
	}
	else {
		c = Cast<ACharacter>(a);
	}

	qp_characterMap.Add(qp_name, c);
	return c;
}


void UQPGIM_Character::QP_CollectCharacter(FString key, ACharacter* character) {
	UQPWM_Actor::qp_staticObject->QP_CollectActor(key,character);
	qp_characterMap.Remove(key);

}

ACharacter* UQPGIM_Character::QP_ChangeMainCharacter(FString collkey, ACharacter* character, FString qp_name, FTransform T) {
	UQPWM_Actor::qp_staticObject->QP_CollectActor(collkey, character);
	return QP_GetNewCharacter(qp_name, T);
}
