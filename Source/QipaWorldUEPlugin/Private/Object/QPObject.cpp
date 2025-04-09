// QIPAWORLD


#include "Object/QPObject.h"

int32 UQPObject::QP_GetObjId() {
	return qp_objId;
}

void UQPObject::QP_SetObjId(int32 id) {
	qp_objId = id;
}

FName UQPObject::QP_GetObjTag() {
	return qp_objTag;
}

void UQPObject::QP_SetObjTag(FName tag) {
	qp_objTag = tag;
}