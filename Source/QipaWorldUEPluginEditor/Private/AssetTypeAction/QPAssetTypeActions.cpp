// QIPAWORLD


#include "AssetTypeAction/QPAssetTypeActions.h"

 const TArray< FText >& FQPAssetTypeActions::GetSubMenus() const {
	 static const TArray<FText> SubMenu = { FText::FromString("QipaWorld")};
	 return SubMenu;
}