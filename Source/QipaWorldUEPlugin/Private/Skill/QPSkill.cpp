// QIPAWORLD


#include "Skill/QPSkill.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AQPSkill::AQPSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	qp_root = CreateDefaultSubobject<USceneComponent>("qp_root");
	RootComponent = qp_root;
	qp_effect = CreateDefaultSubobject<UParticleSystemComponent>("qp_effect");
	qp_effect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQPSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQPSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

