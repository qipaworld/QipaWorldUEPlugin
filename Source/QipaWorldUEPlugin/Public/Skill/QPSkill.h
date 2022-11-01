// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QPSkill.generated.h"

class UParticleSystemComponent;
class USceneComponent;
/**
 * 技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPSkill();

protected:
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* qp_effect;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* qp_root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
