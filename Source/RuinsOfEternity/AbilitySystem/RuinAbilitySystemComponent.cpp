// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/RuinAbilitySystemComponent.h"

void URuinAbilitySystemComponent::InitializeAbilitySystemData(AActor* InOwningActor, AActor* InAvatarActor)
{
	if (AbilitySystemDataInitialized)
	{
		return;
	}

	AbilitySystemDataInitialized = true;

	// Set the Owning Actor and Avatar Actor. (Used throughout the Gameplay Ability System to get references etc.)
	InitAbilityActorInfo(InOwningActor, InAvatarActor);

	// Check to see if we have authority. (Attribute Sets / Attribute Base Values / Gameplay Abilities / Gameplay Effects should only be added -or- set on authority and will be replicated to the client automatically.)
	if (GetOwnerActor()->HasAuthority())
	{
		// Grant Attribute Sets if the array isn't empty.
		if (!AbilitySystemInitializationData.AttributeSets.IsEmpty())
		{
			for (const TSubclassOf<UAttributeSet> AttributeSetClass : AbilitySystemInitializationData.AttributeSets)
			{
				GetOrCreateAttributeSet(AttributeSetClass);
			}
		}

		// Set base attribute values if the map isn't empty.
		if (!AbilitySystemInitializationData.AttributeBaseValues.IsEmpty())
		{
			for (const TTuple<FGameplayAttribute, float>& AttributeBaseValue : AbilitySystemInitializationData.AttributeBaseValues)
			{
				if (HasAttributeSetForAttribute(AttributeBaseValue.Key))
				{
					SetNumericAttributeBase(AttributeBaseValue.Key, AttributeBaseValue.Value);
				}
			}
		}

		// Grant Gameplay Abilities if the array isn't empty.
		if (!AbilitySystemInitializationData.GameplayAbilities.IsEmpty())
		{
			for (const TSubclassOf<UGameplayAbility> GameplayAbility : AbilitySystemInitializationData.GameplayAbilities)
			{
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1, INDEX_NONE, this);

				GiveAbility(AbilitySpec);
			}
		}

		// Apply Gameplay Effects if the array isn't empty.
		if (!AbilitySystemInitializationData.GameplayEffects.IsEmpty())
		{
			for (const TSubclassOf<UGameplayEffect>& GameplayEffect : AbilitySystemInitializationData.GameplayEffects)
			{
				if (IsValid(GameplayEffect))
				{
					FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
					EffectContextHandle.AddSourceObject(this);

					if (FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingSpec(GameplayEffect, 1, EffectContextHandle); GameplayEffectSpecHandle.IsValid())
					{
						ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), this);
					}
				}
			}
		}
	}

	// Apply the Gameplay Tag container as loose Gameplay Tags. (These are not replicated by default and should be applied on both server and client respectively.)
	if (!AbilitySystemInitializationData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(AbilitySystemInitializationData.GameplayTags);
	}
}

const UAttributeSet* URuinAbilitySystemComponent::GetOrCreateAttributeSet(const TSubclassOf<UAttributeSet>& InAttributeSet)
{
	return GetOrCreateAttributeSubobject(InAttributeSet);
}

void URuinAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	InitializeAbilitySystemData(InOwnerActor, InAvatarActor);
}
