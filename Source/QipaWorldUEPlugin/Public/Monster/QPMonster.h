// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/QPI_GetQPData.h"
#include "Animation/QPC_PlayMontage.h"
#include "Interface/QPI_GetAnimData.h"
#include "Interface/QP_AnimNotify.h"

#include "QPMonster.generated.h"

UCLASS()
class QIPAWORLDUEPLUGIN_API AQPMonster : public ACharacter, public IQPI_GetQPData, public IQPI_GetAnimData , public IQP_AnimNotify
{
	GENERATED_BODY()
public:
	static int qp_characterDataMaxNum;
	/**输入名称*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName qp_assetDataName = "assetDataName";
	/**数据名称*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	//FName qp_playerDataKey = "qp_playerData";
	/**发射魔法炮弹的事件名字*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName QP_AnimNotifyFireName = "QP_AnimNotifyFireName";
	/**结束跳跃的事件名字*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	FName QP_AnimNotifyJunmEndName = "qp_slimeJunmEnd";
	/**玩家数据*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	UQPData* qp_characterData = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	UQPData* qp_animData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	UQPC_PlayMontage* qp_playMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_walkSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_sneakSpeed = 150.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_runSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_sneakMaxAcceleration = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_walkMaxAcceleration = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_runMaxAcceleration = 600.0f;

	/**最大速度是run就是跑，是walk就是走路*/
	float qp_maxSpeed = 250.0f;
	/**是否在跑*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	bool qp_isRun = false;
	/**是否在前行*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	bool qp_isSneak = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	float qp_moveInterpSpeed = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")

	bool qp_isAttacking = false;
	UCharacterMovementComponent* qp_movementC;
	float qp_forwardV = 0.0f;
	float qp_rightV = 0.0f;
	float qp_deltaTime = 0.f;
	class UQPDA_Character* qp_assetData = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPCharacter")
	class UQPC_MaterialAutoRestore* qp_materialAutoRestore = nullptr;
public:
	// Sets default values for this character's properties
	AQPMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UQPData* QP_GetQPData() override;
	virtual class UQPData* QP_GetAnimData() override;
	virtual void QP_AnimNotify(const FName& k) override;
	virtual void QP_PlayAnim(FName name, FName StartSectionName = NAME_None);

};
