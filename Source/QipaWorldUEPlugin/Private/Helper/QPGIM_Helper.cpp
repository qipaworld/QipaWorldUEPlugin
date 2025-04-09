// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/QPGIM_Helper.h"
#include "Helper/QPSG_Helper.h"
#include "Kismet/GameplayStatics.h"
#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_Helper* UQPGIM_Helper::qp_staticObject = nullptr;


bool UQPGIM_Helper::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_Helper::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	qp_staticObject = this;


	QP_LoadHelperData();
	qp_helperSaveData->AddToRoot();
	qp_helperData = UQPGIM_Data::qp_staticObject->QP_GetUQPData(qp_dataName);
	qp_helperData->qp_dataDelegate.AddUObject(this, &UQPGIM_Helper::QP_BindHelperData);

	//qp_loadMapName = UQPDeveloperSettings::QP_GET()->QP_DefaultStartMap;
}

void UQPGIM_Helper::Deinitialize()
{
	
	//qp_soundData->qp_dataDelegate.Remove(qp_handle);
	//QP_SaveSoundData();
	Super::Deinitialize();
}


void UQPGIM_Helper::QP_SetHelperName(FString n)
{
	qp_helperSaveData->qp_helperData.Add(n, "1");
	qp_helperSaveData->qp_helperName = n;
	qp_helperData->QP_AddFString("helperName", n);

	//QP_SaveHelperData();
}



FString UQPGIM_Helper::QP_GetHelperName()
{
	return qp_helperSaveData->qp_helperName;
}

bool UQPGIM_Helper::QP_GetHelperNameState(FString n)
{
	if (qp_helperSaveData) {
		return !qp_helperSaveData->qp_helperData.Contains(n);
	}
	else {
		return false;
	}
}

void UQPGIM_Helper::QP_SaveHelperData()
{

	//UQPSG_Helper* qp_helperSaveGame = Cast<UQPSG_Helper>(UGameplayStatics::CreateSaveGameObject(UQPSG_Helper::StaticClass()));
	if (qp_helperSaveData)
	{

		// 设置（可选）委托。
		//FAsyncSaveGameToSlotDelegate qp_SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		//qp_SavedDelegate.BindUObject(this, &UQPGIM_Helper::QP_SavedDelegate);

		/*qp_helperSaveGame->qp_helperNum = QP_GetHelperNum();
		qp_helperSaveGame->qp_tipNum = QP_GetTipNum();
		qp_helperSaveGame->qp_courseNum = QP_GetCourseNum();*/

		//UGameplayStatics::SaveGameToSlot(qp_soundSaveGame, qp_SaveSlotName, qp_UserIndex);
		// 启动异步保存进程。
		//UGameplayStatics::AsyncSaveGameToSlot(qp_helperSaveData, qp_SaveSlotName,qp_UserIndex, qp_SavedDelegate);
		qp_helperSaveData->QP_AsyncSave();
	}
}

//void UQPGIM_Helper::QP_SavedDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
//{
//
//}

void UQPGIM_Helper::QP_LoadHelperData()
{
	qp_helperSaveData = Cast<UQPSG_Helper>(UGameplayStatics::LoadGameFromSlot(qp_SaveSlotName, qp_UserIndex));
	if (!qp_helperSaveData) {
		qp_helperSaveData = Cast<UQPSG_Helper>(UGameplayStatics::CreateSaveGameObject(UQPSG_Helper::StaticClass()));
		qp_helperSaveData->QP_SetSaveKey(qp_SaveSlotName);
		qp_helperSaveData->QP_SetSaveId(qp_UserIndex);
	}
}


void UQPGIM_Helper::QP_BindHelperData(UQPData* data)
{
	/*qp_helperNum = qp_helperData->QP_Getint32("helperNum");
	qp_tipNum = qp_helperData->QP_Getint32("tipNum");
	qp_courseNum = qp_helperData->QP_Getint32("courseNum");*/
	QP_SaveHelperData();
}
