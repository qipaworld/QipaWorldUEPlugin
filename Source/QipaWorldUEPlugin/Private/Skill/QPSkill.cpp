// QIPAWORLD


#include "Skill/QPSkill.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AQPSkill::AQPSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	qp_niagara = CreateDefaultSubobject<UNiagaraComponent>("qp_effect");
	qp_niagara->SetupAttachment(RootComponent);
	//qp_effect3 = CreateDefaultSubobject<ANiagaraActor>("qp_effe3ct");
	//qp_effect3->SetupAttachment(RootComponent);
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

