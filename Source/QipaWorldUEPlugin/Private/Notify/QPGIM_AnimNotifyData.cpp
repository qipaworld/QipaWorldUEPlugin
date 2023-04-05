// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/QPGIM_AnimNotifyData.h"

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_AnimNotifyData* UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData = nullptr;


bool UQPGIM_AnimNotifyData::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_AnimNotifyData::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_UQPGIM_AnimNotifyData = this;

	qp_animNotifyData = UQPGIM_Data::QP_UQPGIM_Data->QP_GetQPData("UQPGIM_AnimNotifyData");
}

void UQPGIM_AnimNotifyData::Deinitialize()
{
	Super::Deinitialize();
	UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData = nullptr;
}

UQPData* UQPGIM_AnimNotifyData::QP_GetNotifyBaseData(){
	return qp_animNotifyData;
}

UQPData* UQPGIM_AnimNotifyData::QP_GetNotifyData(FString name){
	return qp_animNotifyData->QP_GetUQPData(name);
}
UQPData* UQPGIM_AnimNotifyData::QP_AddNotifyData(FString name){
	return qp_animNotifyData->QP_GetUQPData(name);
}
