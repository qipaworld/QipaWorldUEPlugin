// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QP_AnimNotify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQP_AnimNotify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QIPAWORLDUEPLUGIN_API IQP_AnimNotify
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void QP_AnimNotify(const FName& k) = 0;

};
