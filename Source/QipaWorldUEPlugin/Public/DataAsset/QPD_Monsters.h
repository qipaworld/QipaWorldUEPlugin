// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/QPDataAsset.h"

//#include "Monster/QPMonster.h"
#include "QPD_Monsters.generated.h"

class AQPMonster;
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPD_Monsters : public UQPDataAsset
{
	GENERATED_BODY()
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	TMap<FName, TSubclassOf<AQPMonster>> qp_monsterMap;

	

	
};
