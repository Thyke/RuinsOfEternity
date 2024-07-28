// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/Attributes/RuinAttributeSet.h"
#include "GameplayEffectExtension.h"

URuinAttributeSet::URuinAttributeSet()
{

}

void URuinAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void URuinAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	//{
	//	// Store a local copy of the amount of Damage done and clear the Damage attribute.
	//	const float LocalDamageDone = GetDamage();

	//	SetDamage(0.f);

	//	if (LocalDamageDone > 0.0f)
	//	{
	//		// Apply the Health change and then clamp it.
	//		const float NewHealth = GetCurrentHealth() - LocalDamageDone;

	//		SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
	//	}
	//}

	//else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	//{
	//	// Store a local copy of the amount of Healing done and clear the Healing attribute.
	//	const float LocalHealingDone = GetHealing();

	//	SetHealing(0.f);

	//	if (LocalHealingDone > 0.0f)
	//	{
	//		// Apply the Health change and then clamp it.
	//		const float NewHealth = GetCurrentHealth() + LocalHealingDone;

	//		SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
	//	}
	//}

	/*else*/ if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}
