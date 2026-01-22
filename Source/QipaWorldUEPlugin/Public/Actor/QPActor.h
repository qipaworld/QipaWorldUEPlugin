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


	/**因为自己C++创建的对象没有root节点，所以我加了一个*/
	UPROPERTY(VisibleAnywhere,Category = "QipaWorld|QPActor")
	USceneComponent* qp_root;

	/**如果不为0，就在规定时间内销毁*/
	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPActor")
		float qp_autoDestroy = 0;
	/**是否在规定时间内销毁*/
	//bool qp_isAutoDestroy = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//自动销毁的时候会调用这个。
	virtual void QP_End();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
