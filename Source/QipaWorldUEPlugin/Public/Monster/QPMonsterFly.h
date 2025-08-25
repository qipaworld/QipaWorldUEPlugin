// QIPAWORLD

#pragma once

#include "Monster/QPMonster.h"

//#include "Components/StateTreeReference.h"
//#include "Sound/QP_RandomSoundData.h"
#include "QPMonsterFly.generated.h"




UCLASS()
class QIPAWORLDUEPLUGIN_API AQPMonsterFly : public AQPMonster
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AQPMonsterFly(const FObjectInitializer& ObjectInitializer);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
