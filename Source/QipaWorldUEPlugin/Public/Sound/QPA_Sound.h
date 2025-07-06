// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Components/AudioComponent.h"

#include "QPA_Sound.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Sound : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_Sound();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAudioComponent* qp_audioComponent;
};
