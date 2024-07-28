// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Input/RuinEnhancedInputComponent.h"

URuinEnhancedInputComponent::URuinEnhancedInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void URuinEnhancedInputComponent::AddInputMappings(const URuinInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);
}

void URuinEnhancedInputComponent::RemoveInputMappings(const URuinInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);
}

void URuinEnhancedInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
