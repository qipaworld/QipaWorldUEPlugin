// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "QPPlayerState.generated.h"

struct FQPItem;
class UQPSG_ItemBackpack;
/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	UQPSG_ItemBackpack * qp_itemBackpackSaveData;
	TArray<FQPItem> qp_itemFoods;

	void QP_SaveItems();
	//TArray<FQPItem> qp_itemTransforms;
};
