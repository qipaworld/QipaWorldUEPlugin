// QIPAWORLD


#include "Sound/QPA_Sound.h"

AQPA_Sound::AQPA_Sound() {
	qp_audioComponent = CreateDefaultSubobject<UAudioComponent>("qp_audioComponent");
	qp_audioComponent->SetupAttachment(RootComponent);
}