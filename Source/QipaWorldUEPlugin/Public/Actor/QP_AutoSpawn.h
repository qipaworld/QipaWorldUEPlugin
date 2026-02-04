// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QP_AutoSpawn.generated.h"

class USphereComponent;
class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQP_AutoSpawn : public AQPActor
{
	GENERATED_BODY()
	
	
public:
	UNavigationSystemV1* qp_navSys;
	//FVector v

	UPROPERTY(EditAnywhere, Category = "QipaWorld")
	float qp_maxNum = 10;
	//UPROPERTY(EditAnywhere, Category = "QipaWorld")
	float qp_actorNum = 0;

	UPROPERTY(EditAnywhere, Category = "QipaWorld")
	float qp_radius = 500;

	UPROPERTY(EditAnywhere, Category = "QipaWorld")
	float qp_spawnTimeMin= 50;

	UPROPERTY(EditAnywhere, Category = "QipaWorld")
	float qp_spawnTimeRange = 20;

	float qp_spawnTime = 0;

	UPROPERTY(EditAnywhere, Category = "QipaWorld")
	TSubclassOf<AQPActor> qp_spawnActor;

	virtual void BeginPlay() override;

	
	virtual void Tick(float DeltaTime) override;
	
	virtual AQPActor* QP_Spawn();

	 AQP_AutoSpawn();
#if WITH_EDITOR
	//UPROPERTY(VisibleAnywhere)
	USphereComponent* qp_showSphere;
	//UPROPERTY(VisibleAnywhere)
	UBillboardComponent* qp_billboard;

	void PostEditChangeProperty(FPropertyChangedEvent& Event);

#endif
};
