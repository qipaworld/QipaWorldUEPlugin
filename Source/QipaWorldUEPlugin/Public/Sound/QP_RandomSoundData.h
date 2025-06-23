// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Object/QPObject.h"
#include "QP_RandomSoundData.generated.h"


UENUM(BlueprintType)
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

USTRUCT(BlueprintType, Category = "QipaWorld|Sound")
struct FQP_SoundDataCell
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Sound")
	float qp_volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Sound")
	USoundWave* qp_sound;
};

USTRUCT(BlueprintType, Category = "QipaWorld|Sound")
struct FQP_SoundData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Sound")
	TArray< FQP_SoundDataCell> qp_soundCell;
};
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQP_RandomSoundData : public UQPObject
{
	GENERATED_BODY()
	
};
