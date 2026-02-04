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
	int64 qp_lastTime = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, float> qp_datas;

	//UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	 float QP_GetDataScale() const {
		int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp();

		//UQPDA_Item* itemD = QP_GetItemData(n.qp_itemName);
		//GE->DurationPolicy = itemD->qp_GEType;
		if (!qp_datas.Contains("qp_shelfLife")) {
			return 1;
		}
		float timeR = (1 - (TimestampMs - qp_createTime) / qp_datas["qp_shelfLife"]);
		if (timeR >= 0.7) {

		}
		else if (timeR >= 0.3) {
			timeR = 0.7 - (0.7 - timeR) * 0.5;
		}
		else if (timeR >= 0) {

			timeR = 0.5 - (0.3 - timeR);

		}

		if (timeR < 0) {
			timeR = 0.2 * (1 + timeR);

		}
		return timeR;
	}
	 float QP_GetDataScaleEX() const {
		

		return (1 - (FDateTime::UtcNow().ToUnixTimestamp() - qp_createTime) / qp_datas["qp_shelfLife"]);
		
	 }
	//UFUNCTION(BlueprintCallable, Category = "QipaWorld")
	 int QP_GetFreshType() const {
		int64 TimestampMs = FDateTime::UtcNow().ToUnixTimestamp();

		//UQPDA_Item* itemD = QP_GetItemData(n.qp_itemName);
		//GE->DurationPolicy = itemD->qp_GEType;
		//UE_LOG(LogTemp, Warning, TEXT("___!____%d__))))))))"), (TimestampMs - qp_createTime));
		//UE_LOG(LogTemp, Warning, TEXT("___!____%f__))))))))"), (qp_datas["qp_shelfLife"]));
		if (!qp_datas.Contains("qp_shelfLife")) {
			return 0;
		}
		float timeR = (1 - (TimestampMs - qp_createTime) / qp_datas["qp_shelfLife"]);
		if (timeR >= 0.7) {
			return 0;
		}
		else if (timeR >= 0.3) {
			return 1;
		}
		else if (timeR >= 0) {

			return 2;
		}

		if (timeR < 0) {
			return 3;
		}
		return timeR;
	}
	 bool QP_CheckShelfLife() {
		 /*if (qp_itemName == "_") {
			 return false;
		 }*/
		 //UE_LOG(LogTemp, Warning, TEXT("___!____66dfsdf66666__))))))))"));

		 if (qp_datas.Contains("qp_shelfLife")) {

			 bool b = (FDateTime::UtcNow().ToUnixTimestamp() - qp_createTime) < qp_datas["qp_shelfLife"] * 1.5;
			 if (!b) {
				 qp_itemName = "_";
			 }
			 return b;
		 }
		 else  if (qp_datas.Contains("consume")) {
			 if (!qp_datas["consume"]) {
				 return true;
			 }
		 }
		 //UE_LOG(LogTemp, Warning, TEXT("___!____6666666__))))))))"));

		 return true;

	 }
    //float Rate = 1.f;
};
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_Item : public AQPActor
{
	GENERATED_BODY()
public:
	AQPA_Item();
	static TMap<FName, TMap<FName, float>> qp_allItemTypes;
	FQPItem qp_itemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	FName qp_itemName;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld")
	UStaticMeshComponent* qp_mesh;

	TArray<class UMaterialInstanceDynamic*> qp_materials;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	//USphereComponent* qp_sphereTrigger;
	

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

	 void QP_MakeItemData();
	 UFUNCTION()
	 virtual void QP_OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
