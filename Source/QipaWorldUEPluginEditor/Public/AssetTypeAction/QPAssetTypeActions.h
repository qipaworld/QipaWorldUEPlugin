// QIPAWORLD

#pragma once

//#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
//#include "UObject/NoExportTypes.h"
//#include "QPAssetTypeActions.generated.h"
#include "Sound/QPSoundClass.h"

/**
 * 
 */
//UCLASS()
//QIPAWORLDUEPLUGINEDITOR_API
class  FQPAssetTypeActions : public FAssetTypeActions_Base
{
	//GENERATED_BODY()
public:
	virtual FText GetName() const override { return NSLOCTEXT("Sound", "QipaWorld", "QPSoundClass"); }
	virtual FColor GetTypeColor() const override { return FColor(201, 29, 85); }
	virtual UClass* GetSupportedClass() const override { return UQPSoundClass::StaticClass(); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Sounds; }
	virtual const TArray< FText >& GetSubMenus() const;

};
