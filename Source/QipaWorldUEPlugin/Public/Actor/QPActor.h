// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QPActor.generated.h"

class USceneComponent;
/**
 * 技能的基类
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* qp_root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
