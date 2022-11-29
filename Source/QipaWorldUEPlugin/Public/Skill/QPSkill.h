// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraActor.h"
#include "QPSkill.generated.h"


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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* qp_niagara;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ANiagaraActor* qp_effect3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UNiagaraSystem* qp_effect2;*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* MyCoolFX;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
