// QIPAWORLD


#include "Item/QP_AutoSpawnItem.h"

#include "Item/QPA_Item.h"


AQPActor* AQP_AutoSpawnItem::QP_Spawn() {
	 AQPA_Item* item = (AQPA_Item*)Super::QP_Spawn();
	 if (!item) {
		 return nullptr;
	 }
	 item->QP_MakeItemData();
	 //make
	 return item;
}