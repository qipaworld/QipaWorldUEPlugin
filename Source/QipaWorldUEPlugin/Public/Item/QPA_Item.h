// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
//#include "Material/QPC_FadeMaterials.h"
#include "Components/SphereComponent.h"
#include "Math/Color.h"
#include "Engine/Texture2D.h"
#include "QPA_Item.generated.h"
USTRUCT(BlueprintType)
struct FQPItem
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName qp_itemName = "_";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 qp_createTime = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, float> qp_datas;
    //float Rate = 1.f;
};
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Item : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_Item();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	UStaticMeshComponent* qp_mesh;

	TArray<class UMaterialInstanceDynamic*> qp_materials;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* qp_sphereTrigger;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_emissiveMax = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	float qp_emissiveMin = 0;
	int qp_autoEmissive = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	 UTexture2D* qp_texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	 FLinearColor  qp_color;
	
	 bool qp_isShow = false;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	 float qp_speed = 50;

	 float qp_emissive = 0;

	 UFUNCTION()
	 virtual void QP_OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 UFUNCTION()
	 virtual void QP_OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
