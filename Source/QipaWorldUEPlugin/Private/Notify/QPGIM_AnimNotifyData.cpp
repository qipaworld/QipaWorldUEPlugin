// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/QPGIM_AnimNotifyData.h"

#include "Data/QPGIM_Data.h"
#include "Data/QPData.h"

UQPGIM_AnimNotifyData* UQPGIM_AnimNotifyData::qp_staticObject = nullptr;

//FName UQPGIM_AnimNotifyData::QP_DATA_BASE_NAME = "qp_animNotify";

bool UQPGIM_AnimNotifyData::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UQPGIM_AnimNotifyData::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UQPGIM_Data::StaticClass());

	QP_InitStaticObject();

	qp_animNotifyData = UQPGIM_Data::qp_staticObject->QP_GetUQPData("UQPGIM_AnimNotifyData");
}
void UQPGIM_AnimNotifyData::QP_InitStaticObject() {
	UQPGIM_AnimNotifyData::qp_staticObject = this;
}
void UQPGIM_AnimNotifyData::Deinitialize()
{
	Super::Deinitialize();
	qp_staticObject = nullptr;
}

UQPData* UQPGIM_AnimNotifyData::QP_GetNotifyBaseData(){
	return qp_animNotifyData;
}

UQPData* UQPGIM_AnimNotifyData::QP_GetNotifyData(FName name){
	return qp_animNotifyData->QP_GetUQPData(name);
}
//UQPData* UQPGIM_AnimNotifyData::QP_AddNotifyData(FName name){
//	return qp_animNotifyData->QP_GetUQPData(name);
//}
