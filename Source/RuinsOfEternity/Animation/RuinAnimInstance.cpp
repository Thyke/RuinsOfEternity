// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Animation/RuinAnimInstance.h"
#include "AbilitySystemGlobals.h"
#include "Character/RuinCharacter.h"
#include "Components/RuinCharacterMovementComponent.h"
#include "Animation/Nodes/RuinAnimNode_GameplayTagsBlend.h"
#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif


URuinAnimInstance::URuinAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void URuinAnimInstance::InitializeAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
	AbilitySystemComponent = ASC;
}


#if WITH_EDITOR
EDataValidationResult URuinAnimInstance::IsDataValid(FDataValidationContext& Context) const
{
	Super::IsDataValid(Context);

	GameplayTagPropertyMap.IsDataValid(this, Context);

	return ((Context.GetNumErrors() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void URuinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeAbilitySystem(ASC);
		}
	}
}

void URuinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const ARuinCharacter* Character = Cast<ARuinCharacter>(GetOwningActor());
	if (!Character)
	{
		return;
	}

	URuinCharacterMovementComponent* CharMoveComp = CastChecked<URuinCharacterMovementComponent>(Character->GetCharacterMovement());
}
