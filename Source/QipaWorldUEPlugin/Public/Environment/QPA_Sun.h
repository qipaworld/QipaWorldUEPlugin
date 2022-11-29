// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "QPA_Sun.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Sun : public AQPActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQPA_Sun();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float qp_speed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool qp_static = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void ttt();
};
