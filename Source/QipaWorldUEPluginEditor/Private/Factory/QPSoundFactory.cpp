// QIPAWORLD


#include "Factory/QPSoundFactory.h"
#include "Sound/QPSoundClass.h"

UQPSoundFactory::UQPSoundFactory(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SupportedClass = UQPSoundClass::StaticClass();

    bCreateNew = true;
    bEditAfterNew = true;
}
UObject* UQPSoundFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UQPSoundClass>(InParent, Class, Name, Flags);;
}

bool UQPSoundFactory::ShouldShowInNewMenu() const {
	return true;
}
