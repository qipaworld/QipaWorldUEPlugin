// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "NiagaraComponent.h"

#include "QPA_Niagara.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Niagara : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_Niagara();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UNiagaraComponent* qp_Niagara;
};
