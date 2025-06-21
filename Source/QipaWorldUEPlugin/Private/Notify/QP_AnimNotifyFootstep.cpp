// QIPAWORLD


#include "Notify/QP_AnimNotifyFootstep.h"
#include "Interface/QPI_AnimNotifyFootstep.h"

void UQP_AnimNotifyFootstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    //if (!MeshComp || !MeshComp->GetWorld()) return;
    
    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    IQPI_AnimNotifyFootstep* di = Cast<IQPI_AnimNotifyFootstep>(Owner);
    if (di) {

        FVector FootLocation = MeshComp->GetSocketLocation(qp_boneName);

        FVector Start = FootLocation + FVector(0, 0, 10);
        FVector End = FootLocation - FVector(0, 0, 150);

        FHitResult Hit;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(Owner);

        bool bHit = MeshComp->GetWorld()->LineTraceSingleByChannel(
            Hit,
            Start,
            End,
            ECC_Visibility,
            Params
        );

        if (bHit)
        {
            EQPFootstepType t = EQPFootstepType::DEFAULT;
            if (Hit.GetActor()->Tags.Contains("wood")) {
                t = EQPFootstepType::WOOD;
            }else if (Hit.GetActor()->Tags.Contains("tile")) {
                t = EQPFootstepType::TILE;
            }
            else if (Hit.GetActor()->Tags.Contains("woodAir")) {
                t = EQPFootstepType::WOOD_AIR;
            }
               di->QPI_AnimNotifyFootstep(t, Hit.ImpactPoint, qp_minVolume);
            
            
            //Hit.ImpactPoint
            // 输出命中的材质或对象

            // 可扩展：播放不同脚步声、产生粒子、记录地表类型等
        }


        //di->QP_GetQPData()->QP_GetUQPData(UQPGIM_AnimNotify::QP_DATA_BASE_NAME)->QP_Addbool(qp_animNotifyName,true);
        //return true;
            //UE_LOG(LogTemp, Log, TEXT("Footstep hit: %s"), *qp_boneName.ToString());
        
    //DrawDebugLine(MeshComp->GetWorld(), Start, End, FColor::Green, false, 10.0f, 0, 1.0f);
    }

    
    // 可视化调试
	//IQP_AnimNotify* di = Cast<IQP_AnimNotify>(MeshComp->GetOwner());
	//if (di) {
	//	di->QP_AnimNotify(qp_animNotifyName);
	//	//di->QP_GetQPData()->QP_GetUQPData(UQPGIM_AnimNotifyData::QP_DATA_BASE_NAME)->QP_Addbool(qp_animNotifyName,true);
	//	//return true;
	//}
	//return false;
	//if (UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData) { //用这个判断了是否实在运行中
	//	UQPGIM_AnimNotifyData::QP_UQPGIM_AnimNotifyData->QP_AddNotifyData(qp_animNotifyName);
	//}
}