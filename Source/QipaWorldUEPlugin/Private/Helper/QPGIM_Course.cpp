// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/QPGIM_Course.h"
#include "Helper/QPSG_Course.h"

#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_Course* UQPGIM_Course::qp_staticObject = nullptr;


bool UQPGIM_Course::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Course::Initialize(FSubsystemCollectionBase& Collection)
{
	qp_dataName = TEXT("UQPGIM_Course");
	//qp_SaveSlotName = TEXT("qp_helperCourseSaveGame");

	Super::Initialize(Collection);

	//QP_InitStaticObject();

}
void UQPGIM_Course::QP_InitStaticObject() {
	UQPGIM_Course::qp_staticObject = this;
}
void UQPGIM_Course::Deinitialize()
{
	
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();
	Super::Deinitialize();
}



//void UQPGIM_Course::QP_LoadHelperData()
//{
//	qp_helperSaveData = UQPSaveGame::QP_LoadSaveData<UQPSG_Course>(qp_SaveSlotName, qp_UserIndex);
//
//	//qp_helperSaveData->AddToRoot();
//}