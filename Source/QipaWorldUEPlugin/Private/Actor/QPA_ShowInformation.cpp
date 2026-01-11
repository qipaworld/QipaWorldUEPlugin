// QIPAWORLD


#include "Actor/QPA_ShowInformation.h"


AQPA_ShowInformation::AQPA_ShowInformation() {
	PrimaryActorTick.bCanEverTick = true;



	//qp_camera = CreateDefaultSubobject<UCameraComponent>("qp_camera");
	//qp_springArm = CreateDefaultSubobject<USpringArmComponent>("qp_springArm");
	//qp_springArm->bUsePawnControlRotation = true;
	//qp_materialAutoRestore = CreateDefaultSubobject<UQPC_MaterialAutoRestore>("qp_materialAutoRestore");

	//bUseControllerRotationYaw = false;
	//qp_springArm->SetupAttachment(RootComponent);
	//qp_camera->SetupAttachment(qp_springArm);

	qp_sceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("qp_sceneCaptureComponent2D");
	qp_sceneCaptureComponent2D->SetupAttachment(RootComponent);

	
	qp_showRoot = CreateDefaultSubobject<USceneComponent>("qp_showRoot");
	qp_showRoot->SetupAttachment(RootComponent);

	qp_showStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("qp_showStaticMesh");
	qp_showStaticMesh->SetupAttachment(qp_showRoot);


	qp_showSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("qp_showSkeletalMesh");
	qp_showSkeletalMesh->SetupAttachment(qp_showRoot);
	
}

void AQPA_ShowInformation::BeginPlay()
{
	Super::BeginPlay();
	//qp_data->QP_Addbool("isShow", true);

	qp_data = UQPGIM_BaseData::qp_staticObject->QP_GetShowInformationData();
	
	qp_data->QP_GetUQPData("ControlData")->qp_dataDelegate.AddUObject(this, &AQPA_ShowInformation::QP_DataChange);
	QP_UpdateStatus();
	

}
void AQPA_ShowInformation::QP_UpdateStatus() {
	qp_isStatic = qp_data->QP_Getbool("isStatic");
	//qp_showStaticMesh->SetActive(qp_isStatic);
	//qp_showStaticMesh->SetVisibility(qp_isStatic);

	//qp_showSkeletalMesh->SetActive(!qp_isStatic);
	//qp_showSkeletalMesh->SetVisibility(!qp_isStatic);

	if (qp_isStatic) {
		qp_sceneCaptureComponent2D->RemoveShowOnlyComponent(qp_showSkeletalMesh);
		qp_sceneCaptureComponent2D->ShowOnlyComponent(qp_showStaticMesh);
	}
	else {
		qp_sceneCaptureComponent2D->RemoveShowOnlyComponent(qp_showStaticMesh);
		qp_sceneCaptureComponent2D->ShowOnlyComponent(qp_showSkeletalMesh);
	}
	qp_cameraLength = qp_showRoot->GetRelativeLocation().X;
	qp_r = qp_showRoot->GetRelativeRotation();
	qp_sceneCaptureComponent2D->CaptureScene();
}
//void AQPA_ShowInformation::QP_SetSaveDataName(const FString& n) {
//	qp_saveName = n;
//	this->QP_GetSaveData()->QP_LoadData(qp_saveName);
//}


void AQPA_ShowInformation::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	//qp_data->QP_Addbool("isShow", false);
	Super::EndPlay(EndPlayReason);
}
void AQPA_ShowInformation::QP_DataChange(UQPData* data) {
	if (data->QP_IsChange<FName, bool>("mouseMove", EQPDataValueType::BOOL)) {
		qp_isMouseMove = data->QP_Getbool("mouseMove");
	}
	if (data->QP_IsChange<FName, float>("mouseMoveX", EQPDataValueType::FLOAT)) {
		qp_rX = data->QP_Getfloat("mouseMoveX");
		qp_rY = data->QP_Getfloat("mouseMoveY");
		qp_r.Yaw = qp_r.Yaw - qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
		qp_r.Roll = qp_r.Roll + qp_rY * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
		qp_showRoot->SetRelativeRotation(qp_r);
		qp_sceneCaptureComponent2D->CaptureScene();

	}
	if (data->QP_IsChange<FName, float>("MouseWheel", EQPDataValueType::FLOAT)) {
		qp_cameraLength = qp_cameraLength - qp_changeCameraLengthSpeed * data->QP_Getfloat("MouseWheel") * GetWorld()->GetDeltaSeconds();
		qp_showRoot->SetRelativeLocation(FVector(qp_cameraLength, 0, 0));
		//qp_springArm->TargetArmLength = qp_springArm->TargetArmLength + ;
		qp_sceneCaptureComponent2D->CaptureScene();
	}
	
	
}

void AQPA_ShowInformation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!qp_isMouseMove) {
		if (qp_rX != 0 || qp_rY != 0) {
			if (qp_rX > 0) {
				qp_rX = qp_rX - qp_autoSpeed * DeltaTime;
				if (qp_rX < 0) {
					qp_rX = 0;
				}
			}
			else if (qp_rX < 0) {
				qp_rX = qp_rX + qp_autoSpeed * DeltaTime;
				if (qp_rX > 0) {
					qp_rX = 0;
				}
			}
				

			if (qp_rY > 0) {
				qp_rY = qp_rY - qp_autoSpeed * DeltaTime;
				if (qp_rY < 0) {
					qp_rY = 0;
				}
			}
			else if (qp_rY < 0) {
				qp_rY = qp_rY + qp_autoSpeed * DeltaTime;
				if (qp_rY > 0) {
					qp_rY = 0;
				}
			}
			qp_r.Yaw = qp_r.Yaw - qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
			qp_r.Roll = qp_r.Roll + qp_rY * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
			qp_showRoot->SetRelativeRotation(qp_r);
			qp_sceneCaptureComponent2D->CaptureScene();
		}
		

	}
}