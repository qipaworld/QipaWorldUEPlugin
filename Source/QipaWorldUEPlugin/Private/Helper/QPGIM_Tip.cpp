// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/QPGIM_Tip.h"
#include "Helper/QPSG_Tip.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_Tip* UQPGIM_Tip::qp_staticObject = nullptr;


bool UQPGIM_Tip::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Tip::Initialize(FSubsystemCollectionBase& Collection)
{
	qp_dataName = TEXT("UQPGIM_Tip");
	qp_SaveSlotName = TEXT("qp_helperTipSaveGame");

	Super::Initialize(Collection);

	qp_staticObject = this;
}

void UQPGIM_Tip::Deinitialize()
{

	Super::Deinitialize();
}



void UQPGIM_Tip::QP_LoadHelperData()
{
	qp_helperSaveData = Cast<UQPSG_Tip>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (!qp_helperSaveData) {
		qp_helperSaveData = Cast<UQPSG_Tip>(UGameplayStatics::CreateSaveGameObject(UQPSG_Tip::StaticClass()));
		qp_helperSaveData->QP_SetSaveKey(qp_SaveSlotName);
		qp_helperSaveData->QP_SetSaveId(qp_UserIndex);
	}
}
