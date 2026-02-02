// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Actor/QPActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/SkeletalMeshComponent.h"
#include "Data/QPGIM_BaseData.h"

#include "Data/QPData.h"
#include "QPA_ShowInformation.generated.h"

/**
 * 
 */
UCLASS()
class QIPAWORLDUEPLUGIN_API AQPA_ShowInformation : public AQPActor
{
	GENERATED_BODY()
	
public:
	AQPA_ShowInformation();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	USceneCaptureComponent2D* qp_sceneCaptureComponent2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	USceneComponent* qp_showRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	AActor* qp_showActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	//USkeletalMeshComponent* qp_showSkeletalMesh;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	//UCameraComponent* qp_camera;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	//USpringArmComponent* qp_springArm;

	class UQPData* qp_data;

	void QP_DataChange(UQPData* qp_data);
	void QP_UpdateStatus();
	//bool qp_isCharacter = false;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/**鼠标滚轮改变相机距离的速度*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	float qp_changeCameraLengthSpeed = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")
	float qp_rotationSpeed = 20.0f;

	float qp_cameraLength;
	FRotator qp_r;
	float qp_rX;
	float qp_rY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPActor")

	float qp_autoSpeed = 100;
	bool qp_isMouseMove = false;
	FVector qp_sourceVector;
	FVector qp_targetSize;
	virtual void Tick(float DeltaTime) override;

	FName qp_showActorName;

	bool qp_isCaptureScene = false;
};
