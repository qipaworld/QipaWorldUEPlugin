// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QPI_AnimNotifyFootstep.generated.h"


UENUM(BlueprintType, Category = "QipaWorld|AnimNotifyFootstep")
enum class EQPFootstepType :uint8
{
	DEFAULT              UMETA(DisplayName = "default"),
	WOOD              UMETA(DisplayName = "wood"),
	WOOD_AIR              UMETA(DisplayName = "wood air"),
	TILE              UMETA(DisplayName = "tile"),
	WATER              UMETA(DisplayName = "water"),
	DEEP_WATER              UMETA(DisplayName = "deep water"),
	UNDER_WATER              UMETA(DisplayName = "under water"),
};

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
	virtual void QPI_AnimNotifyFootstep(EQPFootstepType, FVector, float) = 0;
};
