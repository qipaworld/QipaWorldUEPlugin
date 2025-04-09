// QIPAWORLD


#include "Animation/QPU_AnimInstance.h"
#include "Data/QPGIM_Data.h"
//void UQPU_AnimInstance::UQPU_AnimInstance() {
//	//Super::NativeInitializeAnimation();
//	//if (!qp_data && UQPGIM_Data::qp_staticObject) {
//		qp_data = UQPGIM_Data::qp_staticObject->QP_GetQPData(GetName());
//	//}
//}
void UQPU_AnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
	if (!qp_data&& UQPGIM_Data::qp_staticObject) {
		qp_data = UQPGIM_Data::qp_staticObject->QP_GetUQPData(GetFName());
	}
}
void UQPU_AnimInstance::NativeUninitializeAnimation() {
	Super::NativeUninitializeAnimation();
	
	if (qp_data && UQPGIM_Data::qp_staticObject) {
		UQPGIM_Data::qp_staticObject->QP_RemoveUQPData(GetFName());
		qp_data = nullptr;
	}
}