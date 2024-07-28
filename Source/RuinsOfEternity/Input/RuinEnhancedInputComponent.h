// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "Input/RuinInputConfig.h"
#include "EnhancedInputComponent.h"
#include "RuinEnhancedInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UObject;

UCLASS()
class RUINSOFETERNITY_API URuinEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	URuinEnhancedInputComponent(const FObjectInitializer& ObjectInitializer);



	void AddInputMappings(const URuinInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const URuinInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

	template<class UserClass, typename FuncType>
	void BindNativeAction(const URuinInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const URuinInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);
};


template<class UserClass, typename FuncType>
void URuinEnhancedInputComponent::BindNativeAction(const URuinInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	UE_LOG(LogTemp, Log, TEXT("BindNativeAction called with InputTag: %s, TriggerEvent: %d"), *InputTag.ToString(), static_cast<int32>(TriggerEvent));

	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		UE_LOG(LogTemp, Log, TEXT("BindNativeAction: Found InputAction for InputTag: %s"), *InputTag.ToString());
		BindAction(IA, TriggerEvent, Object, Func);
	}
	else if (bLogIfNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindNativeAction: InputAction not found for InputTag: %s"), *InputTag.ToString());
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void URuinEnhancedInputComponent::BindAbilityActions(const URuinInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	UE_LOG(LogTemp, Log, TEXT("BindAbilityActions called"));

	check(InputConfig);

	for (const FRuinInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("BindAbilityActions: Binding actions for InputTag: %s"), *Action.InputTag.ToString());

			if (PressedFunc)
			{
				uint32 Handle = BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag).GetHandle();
				BindHandles.Add(Handle);
				UE_LOG(LogTemp, Log, TEXT("BindAbilityActions: Bound PressedFunc for InputTag: %s with Handle: %d"), *Action.InputTag.ToString(), Handle);
			}

			if (ReleasedFunc)
			{
				uint32 Handle = BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle();
				BindHandles.Add(Handle);
				UE_LOG(LogTemp, Log, TEXT("BindAbilityActions: Bound ReleasedFunc for InputTag: %s with Handle: %d"), *Action.InputTag.ToString(), Handle);
			}
		}
	}
}
