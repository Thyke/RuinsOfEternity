// // Copyright (C) 2023 Thyke. All Rights Reserved.


#include "Components/RuinCharacterMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RuinCharacterMovementComponent)

URuinCharacterMovementComponent::URuinCharacterMovementComponent()
{
	GroundFriction = 4.0f;
	MaxWalkSpeed = 375.0f;
	MaxWalkSpeedCrouched = 200.0f;
	MinAnalogWalkSpeed = 25.0f;
	bCanWalkOffLedgesWhenCrouching = true;
}
