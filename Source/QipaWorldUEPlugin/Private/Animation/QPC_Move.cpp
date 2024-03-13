// QIPAWORLD


#include "Animation/QPC_Move.h"

// Sets default values for this component's properties
UQPC_Move::UQPC_Move()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQPC_Move::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQPC_Move::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

