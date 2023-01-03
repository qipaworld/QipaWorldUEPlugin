// QIPAWORLD


#include "Character/QPGIM_Character.h"
#include "Actor/QPWM_Actor.h"
#include "Character/QPDA_Character.h"

UQPGIM_Character* UQPGIM_Character::QP_UQPGIM_Character = nullptr;


bool UQPGIM_Character::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Character::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPGIM_Character = this;

	//qp_soundData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData(qp_soundDataName);

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
	QP_UQPGIM_Character = nullptr;

}
void UQPGIM_Character::QP_AddCharacter(FString qp_name, ACharacter* c) {
	qp_characterMap.Add(qp_name, c);
}
void UQPGIM_Character::QP_Possess(AController* controller, FString qp_name) {
	AQPCharacter* character = Cast<AQPCharacter>(QP_GetCharacter(qp_name));
	controller->Possess(character);
	character->GetCharacterMovement()->SetMovementMode(character->qp_movementMode);
}
ACharacter* UQPGIM_Character::QP_GetCharacter(FString qp_name) {
	if (qp_characterMap.Contains(qp_name))
	{
		return qp_characterMap[qp_name];
	}
	return nullptr;
}
ACharacter* UQPGIM_Character::QP_GetNewCharacter(FString qp_name, FTransform T) {
	AActor* a = UQPWM_Actor::QP_UQPWM_Actor->QP_GetActor(qp_name);
	ACharacter* c;
	if (!a) {
		//qp_character
		UQPDA_Character* data = LoadObject<UQPDA_Character>(nullptr, *(qp_assetPath + qp_name + "." + qp_name + "'"));
	
		//FTransform qp_spawnT = FTransform(GetActorRotation(), location);
		FActorSpawnParameters qp_spawnP;
		qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//qp_attackSkill->
		//float qp_skillSpeed = qp_attackSkill.QP_GetMovement()->InitialSpeed;
		//qp_attackSkill->QP_GetMovement()->InitialSpeed = qp_skillSpeed + GetCharacterMovement()->GetLastUpdateVelocity()->Size();
		
		c = GetWorld()->SpawnActor<ACharacter>(data->qp_character, T, qp_spawnP);

	}
	else {
		c = Cast<ACharacter>(a);
	}

	qp_characterMap.Add(qp_name, c);
	return c;
}


void UQPGIM_Character::QP_CollectCharacter(FString key, ACharacter* character) {
	UQPWM_Actor::QP_UQPWM_Actor->QP_CollectActor(key,character);
	qp_characterMap.Remove(key);

}

ACharacter* UQPGIM_Character::QP_ChangeMainCharacter(FString collkey, ACharacter* character, FString qp_name, FTransform T) {
	UQPWM_Actor::QP_UQPWM_Actor->QP_CollectActor(collkey, character);
	return QP_GetNewCharacter(qp_name, T);
}
