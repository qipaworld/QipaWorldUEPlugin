﻿// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QPSkill.generated.h"

class UParticleSystemComponent;
/**
 * 技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPSkill : public AQPActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPSkill();

protected:
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* qp_effect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};