// QIPAWORLD

#pragma once

#include "CoreMinimal.h"

#include "Component/QPComponent.h"
#include "QPC_MaterialDissolve.generated.h"

/**
 * 这个类和UQPC_MaterialAutoRestore 内容一样，
 * 以后可以改改
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_MaterialDissolve : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPC_MaterialDissolve();
public:
	virtual void BeginPlay() override;
	//virtual void ReceiveTick(float DeltaTime) override;
	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)override;
public:
	//UStaticMeshComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPMateria")
	UMeshComponent* qp_mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPMateria")
		FName qp_amountName = "qp_amount";
	///**恢复粒子特效*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	class UNiagaraComponent* qp_restoreNg = nullptr;
	/**恢复粒子特效*/
	UPROPERTY(EditAnywhere, Category = "QipaWorld|QPMateria")
	class	UNiagaraSystem* qp_restoreNgClass;
	///**支持溶解的材质*/

	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> qp_materialDissolves;

		bool isDissolve = false;
	
	///**不支持溶解的材质，如果设置了这个，可以提高效率*/
		UPROPERTY()
		TArray<class UMaterial*> qp_materials;

	///**激活恢复粒子特效的最小值*/

	/**变身时候的那个材质修复的进度*/
	float qp_matAmount = 1;

	/**变身时候的那个材质修复的速度*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPMateria")
		float qp_matAmountSpeed = 0.1f;

	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMateria")
	void QP_SetMatAmount(float amount = 0.f);
	//void QP_SetRestoreNiagara(class UNiagaraComponent* ng);
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMateria")
	void QP_Play();
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPMateria")
	void QP_Stop();
};
