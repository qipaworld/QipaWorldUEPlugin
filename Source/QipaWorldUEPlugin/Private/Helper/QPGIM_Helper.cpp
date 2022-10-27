// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/QPGIM_Helper.h"
#include "Helper/QPSG_Helper.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_Helper* UQPGIM_Helper::QP_UQPGIM_Helper = nullptr;


bool UQPGIM_Helper::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Helper::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPGIM_Helper = this;

	qp_helperData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData("helperData");

	QP_LoadHelperData();

	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Helper::Deinitialize()
{
	
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();
	Super::Deinitialize();
}


void UQPGIM_Helper::QP_SetHelperNum(int32 n)
{
	qp_helperData->QP_Addint32("helperNum", n);
}

void UQPGIM_Helper::QP_SetTipNum(int32 n)
{
	qp_helperData->QP_Addint32("tipNum", n);
}

void UQPGIM_Helper::QP_SetCourseNum(int32 n)
{
	qp_helperData->QP_Addint32("courseNum", n);
}

int32 UQPGIM_Helper::QP_GetHelperNum()
{
	return 	qp_helperData->QP_Getint32("helperNum");
}

int32 UQPGIM_Helper::QP_GetTipNum()
{
	return qp_helperData->QP_Getint32("tipNum");
}

int32 UQPGIM_Helper::QP_GetCourseNum()
{
	return qp_helperData->QP_Getint32("courseNum");
}

void UQPGIM_Helper::QP_SaveHelperData()
{

	UQPSG_Helper* qp_helperSaveGame = Cast<UQPSG_Helper>(UGameplayStatics::CreateSaveGameObject(UQPSG_Helper::StaticClass()));
	if (qp_helperSaveGame)
	{

		// 设置（可选）委托。
		FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		qp_SavedDelegate.BindUObject(this, &UQPGIM_Helper::QP_SavedDelegate);

		qp_helperSaveGame->qp_helperNum = QP_GetHelperNum();
		qp_helperSaveGame->qp_tipNum = QP_GetTipNum();
		qp_helperSaveGame->qp_courseNum = QP_GetCourseNum();

		//UGameplayStatics::SaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName, qp_UserIndex);
		// 启动异步保存进程。
		UGameplayStatics::AsyncSaveGameToSlot(qp_helperSaveGame, qp_SaveSlotName,qp_UserIndex, qp_SavedDelegate);
	}
}

void UQPGIM_Helper::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}

void UQPGIM_Helper::QP_LoadHelperData()
{
	UQPSG_Helper* qp_LoadHelperData = Cast<UQPSG_Helper>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (qp_LoadHelperData)
	{

		QP_SetHelperNum(qp_LoadHelperData->qp_helperNum);
		QP_SetTipNum(qp_LoadHelperData->qp_tipNum);
		QP_SetCourseNum(qp_LoadHelperData->qp_courseNum);
		
	}
	else
	{
		QP_SetHelperNum(1);
		QP_SetTipNum(1);
		QP_SetCourseNum(1);
	}

	//qp_handle = qp_soundData->qp_dataDelegate.AddUObject(this, &UQPGIM_Sound::QP_BindSoundData);
	qp_helperData->qp_dataDelegate.AddUObject(this, &UQPGIM_Helper::QP_BindHelperData);

}


void UQPGIM_Helper::QP_BindHelperData(const UQPData* data)
{
	/*qp_helperNum = qp_helperData->QP_Getint32("helperNum");
	qp_tipNum = qp_helperData->QP_Getint32("tipNum");
	qp_courseNum = qp_helperData->QP_Getint32("courseNum");*/
	QP_SaveHelperData();
}
