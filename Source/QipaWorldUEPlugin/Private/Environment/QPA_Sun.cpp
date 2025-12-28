// QIPAWORLD


#include "Environment/QPA_Sun.h"
#include "Map/QPGIM_Map.h"

AQPA_Sun::AQPA_Sun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//qp_speed;

	//qp_static;
	/*qp_effect = CreateDefaultSubobject<UParticleSystemComponent>("qp_effect");
	qp_effect->SetupAttachment(RootComponent);*/
}

// Called when the game starts or when spawned
void AQPA_Sun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQPA_Sun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!qp_static) {
		
		AddActorLocalRotation(FRotator( DeltaTime * qp_speed, 0, 0));
		UQPGIM_Map::qp_staticObject->qp_mapTime = (GetActorRotation().Pitch+180.f )/ 360.f;
		UQPGIM_Map::qp_staticObject->qp_mapTimeEx = (1.0f - FMath::Abs(UQPGIM_Map::qp_staticObject->qp_mapTime - 0.5f) * 2.0f);
	}
}