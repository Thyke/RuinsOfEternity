// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/Attributes/RuinAttributeSet.h"
#include "GameplayEffectExtension.h"

URuinAttributeSet::URuinAttributeSet()
{
	MaximumHealth = 0.0f;
	CurrentHealth = 0.0f;
	HealthRegeneration = 0.0f;
}

void URuinAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumHealthAttribute())
	{
		AdjustAttributeForMaxChange(CurrentHealth, MaximumHealth, NewValue, GetCurrentHealthAttribute());
	}
}

void URuinAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);

		if (LocalDamageDone > 0.0f)
		{
			// Apply the Health change and then clamp it.
			const float NewHealth = GetCurrentHealth() - LocalDamageDone;

			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
		}
	}

	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Store a local copy of the amount of Healing done and clear the Healing attribute.
		const float LocalHealingDone = GetHealing();

		SetHealing(0.f);

		if (LocalHealingDone > 0.0f)
		{
			// Apply the Health change and then clamp it.
			const float NewHealth = GetCurrentHealth() + LocalHealingDone;

			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
		}
	}

	else if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaximumHealth()));
	}

	else if (Data.EvaluatedData.Attribute == GetHealthRegenerationAttribute())
	{
		SetHealthRegeneration(FMath::Clamp(GetHealthRegeneration(), 0.0f, GetMaximumHealth()));
	}
}
