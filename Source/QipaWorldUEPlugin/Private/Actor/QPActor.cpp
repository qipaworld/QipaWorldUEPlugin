// QIPAWORLD


#include "Actor/QPActor.h"
// Sets default values
AQPActor::AQPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	qp_root = CreateDefaultSubobject<USceneComponent>("qp_root");
	RootComponent = qp_root;
}

// Called when the game starts or when spawned
void AQPActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

