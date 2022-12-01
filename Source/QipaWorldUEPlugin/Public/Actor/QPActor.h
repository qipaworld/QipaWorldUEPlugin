// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QPActor.generated.h"

class USceneComponent;
/**
 * 所有QPActor的基类
 */
UCLASS(Meta = (ShortToolTip = "所有QPActor的基类"))
class QIPAWORLDUEPLUGIN_API AQPActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPActor();

protected:
	/**因为自己C++创建的对象没有root节点，所以我加了一个*/
	UPROPERTY(VisibleAnywhere,Category = "QipaWorld|QPActor")
	USceneComponent* qp_root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
