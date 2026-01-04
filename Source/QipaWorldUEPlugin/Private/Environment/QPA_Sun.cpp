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
	qp_sunRotation = GetActorRotation().Pitch;
}

// Called every frame
void AQPA_Sun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!qp_static) {
		qp_sunRotation += (DeltaTime * qp_speed);
		if (qp_sunRotation > 360) {
			qp_sunRotation -= 360;
		}
		AddActorLocalRotation(FRotator( DeltaTime * qp_speed, 0, 0));
		SetActorRotation(FRotator(qp_sunRotation, 0, 0));
		

		UQPGIM_Map::qp_staticObject->QP_SetSunRotation(qp_sunRotation / 360.f);
		
	}
}