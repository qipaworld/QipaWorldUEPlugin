// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Data/QPSaveGame.h"
#include "QPBaseDataSave.generated.h"

/**
 *  ·ÏÆú
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPBaseDataSave : public UQPSaveGame
{
	GENERATED_BODY()
public:
	
	//UPROPERTY()
	//float qp_version = 1.0;
	//// if key to v = true , is init completed

	//UPROPERTY()
	//TMap<int32,bool> qp_initMaps;
	//// if key to v = true , is tiped
	//UPROPERTY()
	//TMap<int32, bool> qp_tipMaps;

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPSound")
	//bool QP_SetInitMap(FString k, bool v);
};
