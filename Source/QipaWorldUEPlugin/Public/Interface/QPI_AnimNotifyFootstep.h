// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sound/QP_RandomSoundData.h"
#include "QPI_AnimNotifyFootstep.generated.h"




UENUM(BlueprintType, Category = "QipaWorld|AnimNotifyFootstep")
enum class EQPFootstepAutoVolumeType :uint8
{
	NONE              UMETA(DisplayName = "none"),
	XY              UMETA(DisplayName = "xy"),
	XYZ              UMETA(DisplayName = "xyz"),
	Z              UMETA(DisplayName = "z"),
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQPI_AnimNotifyFootstep : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QIPAWORLDUEPLUGIN_API IQPI_AnimNotifyFootstep
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void QPI_AnimNotifyFootstep(EQPFootstepType, const FHitResult&, float) = 0;
};
