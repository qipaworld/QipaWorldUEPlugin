// QIPAWORLD

#pragma once

#include "CoreMinimal.h"

#include "Component/QPComponent.h"
#include "QPC_MaterialAutoRestore.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API UQPC_MaterialAutoRestore : public UQPComponent
{
	GENERATED_BODY()
public:
	UQPC_MaterialAutoRestore();
public:
	virtual void BeginPlay() override;
	//virtual void ReceiveTick(float DeltaTime) override;
	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)override;
public:
	
	/// 是否可以恢复
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|MaterialAutoRestore")
	bool qp_isRestore = true;
	bool qp_isDissolveMat = true;
	class USkeletalMeshComponent* qp_mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|MaterialAutoRestore")
		FName qp_amountName = "qp_amount";
	///**恢复粒子特效*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPSlime")
	class UNiagaraComponent* qp_restoreNg = nullptr;
	/**恢复粒子特效*/
	UPROPERTY(EditAnywhere, Category = "QipaWorld|MaterialAutoRestore")
	class	UNiagaraSystem* qp_restoreNgClass;
	///**支持溶解的材质*/

	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> qp_materialDissolves;

	///**支持溶解的材质实例*/
	//UPROPERTY()
	//TArray<UMaterialInstanceDynamic*> qp_materialInstanceDynamices;
	
	///**不支持溶解的材质，你必须设置这个，数量需要与可变材质一致，它用于材质不需要特效时的性能节约。如果设置了这个，可以提高效率*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|MaterialAutoRestore")
		TArray<class UMaterial*> qp_materials;

	bool qp_isRestoreNg = false;
	///**激活恢复粒子特效的最小值*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|MaterialAutoRestore")
		float qp_restoreNgMin = 0.6f;
	/**变身时候的那个材质修复的进度*/
	float qp_matAmount = 1;

	/**变身时候的那个材质修复的速度*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|MaterialAutoRestore")
		float qp_matAmountSpeed = 0.1f;

	
	UFUNCTION(BlueprintCallable, Category = "QipaWorld|MaterialAutoRestore")
	void QP_SetMatAmount(float amount = 0.f);
	//void QP_SetRestoreNiagara(class UNiagaraComponent* ng);

};
