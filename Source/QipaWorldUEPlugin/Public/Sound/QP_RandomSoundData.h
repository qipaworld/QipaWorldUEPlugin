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
	USER_1              UMETA(DisplayName = "user 1"),
	USER_2              UMETA(DisplayName = "user 2"),
	USER_3              UMETA(DisplayName = "user 3"),
	USER_4              UMETA(DisplayName = "user 4"),
	USER_5              UMETA(DisplayName = "user 5"),
	USER_6              UMETA(DisplayName = "user 6"),
	USER_7              UMETA(DisplayName = "user 7"),
};

USTRUCT(BlueprintType, Category = "QipaWorld|Sound")
struct FQP_SoundDataCell
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Sound")
	float qp_volume = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|Sound")
	USoundWave* qp_sound = nullptr;
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
