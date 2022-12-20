// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QPSoundFactory.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGINEDITOR_API UQPSoundFactory : public UFactory
{
	GENERATED_BODY()
public:
	UQPSoundFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};
