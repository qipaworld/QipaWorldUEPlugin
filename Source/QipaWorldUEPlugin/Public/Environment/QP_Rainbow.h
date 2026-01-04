// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Map/QPGIM_Map.h"
#include "QP_Rainbow.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQP_Rainbow : public AQPActor
{
	GENERATED_BODY()
	
public:
	AQP_Rainbow();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	UStaticMeshComponent* qp_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	int  qp_materialIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")

	UMaterialInstanceDynamic* qp_material = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	FName qp_parameterValueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_parameterValueMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_parameterValueMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	float qp_showMax = 0.8;

	float qp_parameterValueRange;
	float qp_outRange;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|FadeMaterial")
	EQPSunType qp_showType;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void QP_BindMapData(UQPData* data);

};
