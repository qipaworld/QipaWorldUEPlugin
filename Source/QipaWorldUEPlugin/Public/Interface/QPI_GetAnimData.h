// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QPI_GetAnimData.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQPI_GetAnimData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QIPAWORLDUEPLUGIN_API IQPI_GetAnimData
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
public:
	
	virtual class UQPData* QP_GetAnimData() = 0;
};
