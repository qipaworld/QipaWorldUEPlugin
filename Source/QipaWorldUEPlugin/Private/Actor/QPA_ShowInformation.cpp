// QIPAWORLD


#include "Actor/QPA_ShowInformation.h"
#include "Character/QPGIM_Character.h"
#include "Actor/QPGIM_Actor.h"
#include "Character/QPDA_Character.h"

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
	

	qp_rollRoot = CreateDefaultSubobject<USceneComponent>("qp_rollRoot");
	qp_rollRoot->SetupAttachment(qp_showRoot);

	qp_yawRoot = CreateDefaultSubobject<USceneComponent>("qp_yawRoot");
	qp_yawRoot->SetupAttachment(qp_rollRoot);

	//qp_showStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("qp_showStaticMesh");
	//qp_showStaticMesh->SetupAttachment(qp_showRoot);


	//qp_showSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("qp_showSkeletalMesh");
	//qp_showSkeletalMesh->SetupAttachment(qp_showRoot);
	
}

void AQPA_ShowInformation::BeginPlay()
{
	Super::BeginPlay();
	//qp_data->QP_Addbool("isShow", true);

	qp_data = UQPGIM_BaseData::qp_staticObject->QP_GetShowInformationData();
	
	//qp_targetVector = qp_showStaticMesh->GetRelativeLocation();

	//FVector Min;
	//FVector Max;

	//qp_showStaticMesh->GetLocalBounds(Min, Max);
	//UQPUtil::QP_LOG(().ToString());

	qp_targetSize = FVector(100,100,100);//Max - Min;
	qp_sourceVector = qp_showRoot->GetRelativeLocation();
	qp_data->QP_GetUQPData("ControlData")->qp_dataDelegate.AddUObject(this, &AQPA_ShowInformation::QP_DataChange);
		//qp_sceneCaptureComponent2D->ShowOnlyComponent(qp_showActor);
		//qp_sceneCaptureComponent2D->ShowOnlyComponent(qp_showSkeletalMesh);

	/*if (isStatic) {
		qp_sceneCaptureComponent2D->RemoveShowOnlyComponent(qp_showSkeletalMesh);
	}
	else {
		qp_sceneCaptureComponent2D->RemoveShowOnlyComponent(qp_showStaticMesh);
	}*/
	

}
void AQPA_ShowInformation::QP_UpdateStatus() {
	//bool isStatic = true;
	FName n = qp_data->QP_GetFName("showActorName");
	if (n == qp_showActorName) {
		return;
	}
	qp_showActorName = n;
	qp_sceneCaptureComponent2D->ClearShowOnlyComponents();
	
	if (qp_showActor) {
		qp_showRoot->SetRelativeScale3D(FVector(1, 1, 1));
		qp_showRoot->SetRelativeLocation(qp_sourceVector);
		qp_rollRoot->SetRelativeRotation(FRotator(0,0,0));
		qp_yawRoot->SetWorldRotation(FRotator(0, 0, 0));
		qp_showActor->Destroy();
	}

	qp_showActor = UQPGIM_Actor::qp_staticObject->QP_GetDefaultActor(qp_showActorName, qp_yawRoot->GetComponentTransform());
	/*if (qp_data->QP_Getbool("qp_showIsSelf")) {

		FActorSpawnParameters qp_spawnP;
		qp_spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		qp_showActor = GetWorld()->SpawnActor<AActor>(UQPGIM_Character::qp_staticObject->QP_GetCharacterData(n)->qp_showActor, qp_showRoot->GetComponentTransform(), qp_spawnP);

	}*/
	

	

	qp_showActor->GetRootComponent()->AttachToComponent(qp_yawRoot,FAttachmentTransformRules::KeepWorldTransform);
	
	
	FVector ActorSize(0, 0, 0);
	FVector CenterOffset(0, 0, 0);

	FVector MinBox(FLT_MAX, FLT_MAX, FLT_MAX);
	FVector MaxBox(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	TArray<UPrimitiveComponent*> Comps;
	qp_showActor->GetComponents<UPrimitiveComponent>(Comps);
	
	FTransform CompTransform;
	for (UPrimitiveComponent* Comp : Comps)
	{
		/*if (!MeshComp->IsRegistered())
			continue;*/
		qp_sceneCaptureComponent2D->ShowOnlyComponent(Comp);

		FBox LocalBox(ForceInit);

		if (USkeletalMeshComponent* SK = Cast<USkeletalMeshComponent>(Comp))
		{
			if (!SK->SkeletalMesh)
				continue;
			//UQPUtil::QP_LOG(SK->GetName());

			// 使用 SkeletalMesh 原始 Bounds，忽略动画
			FBoxSphereBounds MeshBounds = SK->SkeletalMesh->GetBounds();
			LocalBox = MeshBounds.GetBox();
			CompTransform = SK->GetComponentTransform();

		}
		else if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Comp))
		{
			if (!SM->GetStaticMesh())
				continue;
			//UQPUtil::QP_LOG(SM->GetName());

			FBoxSphereBounds MeshBounds = SM->GetStaticMesh()->GetBounds();
			LocalBox = MeshBounds.GetBox();
			CompTransform = SM->GetComponentTransform();
		}
		else {
			continue;
		}
		
		LocalBox = LocalBox.TransformBy(CompTransform);

		
		MinBox.X = FMath::Min(MinBox.X, LocalBox.Min.X);
		MinBox.Y = FMath::Min(MinBox.Y, LocalBox.Min.Y);
		MinBox.Z = FMath::Min(MinBox.Z, LocalBox.Min.Z);

		MaxBox.X = FMath::Max(MaxBox.X, LocalBox.Max.X);
		MaxBox.Y = FMath::Max(MaxBox.Y, LocalBox.Max.Y);
		MaxBox.Z = FMath::Max(MaxBox.Z, LocalBox.Max.Z);
	}

	// 计算大小
	ActorSize = MaxBox - MinBox;

	// 根节点世界位置
	//FVector RootPos = qp_showActor->GetRootComponent() ? qp_showActor->GetRootComponent()->GetComponentLocation() : qp_showActor->GetActorLocation();

	// 模型中心
	//FVector Center = (MinBox + MaxBox) * 0.5f;

	// 偏移 = 模型中心 - 根节点
	//CenterOffset = Center - RootPos;
	

	

	//FVector Origin;
	//FVector Extent;
	//qp_showActor->GetActorBounds(
	//	/*bOnlyCollidingComponents=*/ false,
	//	Origin,
	//	Extent
	//);



	//if (qp_showActor) {

		//qp_showSkeletalMesh->SetSkeletalMesh(qp_showActor);

		//FBox Bounds = qp_showActor->GetBounds().GetBox();
	//FVector Size = ActorSize * 2;
	//UQPUtil::QP_LOG(ActorSize.ToString());
	//UQPUtil::QP_LOG(CenterOffset.ToString());
	//FVector ov = Bounds.GetCenter();
	//qp_showActor->SetActorRelativeLocation(-CenterOffset);
	//qp_showSkeletalMesh->SetRelativeLocation((- ov));
	float s = ActorSize.X;
	if (s < ActorSize.Y) {
		s = ActorSize.Y;
	}
	if (s < ActorSize.Z) {
		s = ActorSize.Z;
	}
	s = qp_targetSize.X / s;
	//qp_showActor->
	//qp_showRoot->SetRelativeScale3D
	qp_showRoot->SetRelativeScale3D(FVector(s,s,s));
		
	//}
	/*else {

		

		UStaticMesh* sm_ = (UStaticMesh*)qp_data->QP_GetUObject("qp_showMesh");
		qp_showStaticMesh->SetStaticMesh(sm_);

		
		FBox Bounds = sm_->GetBounds().GetBox();
		FVector Size = Bounds.GetSize();
		FVector ov = Bounds.GetCenter();

		qp_showStaticMesh->SetRelativeLocation((-ov));
		float s = Size.X;
		if (s < Size.Y) {
			s = Size.Y;
		}
		if (s < Size.Z) {
			s = Size.Z;
		}
		s = qp_targetSize.X / s;
		qp_showStaticMesh->SetWorldScale3D(FVector(s, s, s));
	}*/
	qp_cameraLength = qp_showRoot->GetRelativeLocation().X;
	//FRotator qp_r = qp_showRoot->GetRelativeRotation();
	//qp_Roll_Last =
	qp_rX_Last = 0;
	qp_rY_Last = 0;
	//qp_sceneCaptureComponent2D->CaptureScene();
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
		//qp_rX_Last = qp_rX_Last - qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
		qp_rY_Last = qp_rY_Last + qp_rY * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;


		qp_rollRoot->SetRelativeRotation(FRotator(qp_rY_Last, 0, 0));
		qp_yawRoot->AddWorldRotation(FRotator(0, -qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed, 0));
		
		//SetRelativeRotation
		//qp_sceneCaptureComponent2D->CaptureScene();

	}
	else if (data->QP_IsChange<FName, float>("MouseWheel", EQPDataValueType::FLOAT)) {
		qp_cameraLength = qp_cameraLength - qp_changeCameraLengthSpeed * data->QP_Getfloat("MouseWheel") * GetWorld()->GetDeltaSeconds();
		qp_showRoot->SetRelativeLocation(FVector(qp_cameraLength, 0, 0));
		//qp_springArm->TargetArmLength = qp_springArm->TargetArmLength + ;
		//qp_sceneCaptureComponent2D->CaptureScene();
	}
	if (data->QP_IsChange<FName, bool>("qp_isCaptureScene", EQPDataValueType::BOOL)) {
		//qp_cameraLength = qp_cameraLength - qp_changeCameraLengthSpeed * data->QP_Getfloat("MouseWheel") * GetWorld()->GetDeltaSeconds();
		//qp_showRoot->SetRelativeLocation(FVector(qp_cameraLength, 0, 0));
		////qp_springArm->TargetArmLength = qp_springArm->TargetArmLength + ;
		//qp_sceneCaptureComponent2D->CaptureScene();
		qp_isCaptureScene = data->QP_Getbool("qp_isCaptureScene");
		if (qp_isCaptureScene) {
			QP_UpdateStatus();
		}
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
			//qp_rX_Last = qp_rX_Last - qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
			qp_rY_Last = qp_rY_Last + qp_rY * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed;
			//qp_showRoot->SetRelativeRotation(qp_r);
			//qp_showActor->SetActorRelativeRotation(FRotator(0, qp_rX_Last, qp_rY_Last));//SetRelativeRotation
			qp_rollRoot->SetRelativeRotation(FRotator(qp_rY_Last, 0, 0));
			qp_yawRoot->AddWorldRotation(FRotator(0, -qp_rX * GetWorld()->GetDeltaSeconds() * qp_rotationSpeed, 0));

		}
		

	}
	if (qp_isCaptureScene) {
		qp_sceneCaptureComponent2D->CaptureScene();
	}
}