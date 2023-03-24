// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Component/QPComponent.h"
#include "Localization/QPGIM_Localization.h"
#include "Engine/Font.h"
#include "Text3DComponent.h"
#include "Data/QPData.h"
#include "QPC_Text3dL10N.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (QipaWorld), meta = (BlueprintSpawnableComponent))
class QIPAWORLDUEPLUGIN_API UQPC_Text3dL10N : public UQPComponent
{
	GENERATED_BODY()
public:
	//这个是你要国际化的3d字体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QipaWorld|QPText3D")
	TObjectPtr<class UText3DComponent> qp_text3dComponent;
public:
		virtual void BeginPlay();

		FString qp_fontPath = "";


		/**监听国际化地区改变事件*/
		void QP_L10NChange(UQPData* data);
		/**改变字体*/
		virtual void QP_ChangeFontSlate();
};
