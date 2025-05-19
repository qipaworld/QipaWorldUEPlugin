// QIPAWORLD

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPUtil.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOGQipaWorld, Log, All);






UCLASS()
class QIPAWORLDUEPLUGIN_API UQPUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//UFUNCTION(BlueprintCallable, Category = "QPUtil")
	//static void QP_ScreenFullWindowed();

	UFUNCTION(BlueprintCallable, Category = "QPUtil")
	static void QP_ScreenResolution(float percentage = 0.9f);
	// Return true if the object is usable : non-null and not pending kill
	UFUNCTION(BlueprintPure, Category = "QPUtil")
	static FIntPoint QP_GetFullScreenResolution(float percentage = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "QPUtil")

	static void QP_UpdateMouse(bool show, APlayerController* controller = nullptr, class UWidget* InWidgetToFocus = nullptr, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, bool bHideCursorDuringCapture = true, const bool bFlushInput = false);

	UFUNCTION(BlueprintCallable, Category = "QPUtil")

	static void QP_LOG(const FString& Message, const FColor& Color = FColor::Yellow, float Duration = 5.0f);




	template<typename T>
	static void QP_LOG_EX(const FString& m,const T& Value)
	{
		if constexpr (std::is_same<T, FString>::value)
		{
			QP_LOG(m+ Value);
		}
		else if constexpr (std::is_same<T, FName>::value)
		{
			QP_LOG(m+ Value.ToString());
		}
		else if constexpr (std::is_same<T, FText>::value)
		{
			QP_LOG(m+ Value.ToString());
		}
		else if constexpr (std::is_same<T, const TCHAR*>::value || std::is_same<T, TCHAR*>::value)
		{
			QP_LOG(m+ FString(Value));
		}
		else if constexpr (std::is_same<T, FVector>::value)
		{
			QP_LOG(m + (Value.ToString()));
		}
		else if constexpr (std::is_same<T, bool>::value)
		{
			QP_LOG(m+ (Value ? TEXT("true") : TEXT("false")));
		}
		else if constexpr (TIsPointer<T>::Value)
		{
			using PointeeType = typename TRemovePointer<T>::Type;

			if constexpr (TIsDerivedFrom<PointeeType, UObject>::Value)
			{
				QP_LOG(m+ (Value ? Value->GetName() : TEXT("nullptr")));
			}
			else
			{
				QP_LOG(m+ (Value ? FString::Printf(TEXT("Pointer: 0x%p"), Value) : TEXT("nullptr")));
			}
		}
		else if constexpr (TIsArithmetic<T>::Value || TIsEnum<T>::Value)
		{
			QP_LOG(m+ LexToString(Value));
		}
		else
		{
			QP_LOG("[Unsupported Type]");
		}
	}
	

};
