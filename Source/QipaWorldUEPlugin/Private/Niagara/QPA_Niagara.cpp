// QIPAWORLD


#include "Niagara/QPA_Niagara.h"

AQPA_Niagara::AQPA_Niagara() {
	qp_Niagara = CreateDefaultSubobject<UNiagaraComponent>("qp_Niagara");
	qp_Niagara->SetupAttachment(RootComponent);
}