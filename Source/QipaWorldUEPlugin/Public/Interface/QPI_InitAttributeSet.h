// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "Monster/QPMonster.h"

#include "QPI_InitAttributeSet.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQPI_InitAttributeSet : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class QIPAWORLDUEPLUGIN_API IQPI_InitAttributeSet
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void QPI_InitAttributeSet( class AQPMonster* k) = 0;

};
