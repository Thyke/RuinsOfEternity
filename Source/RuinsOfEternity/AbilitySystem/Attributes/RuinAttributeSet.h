// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/RuinAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "RuinAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RUINSOFETERNITY_API URuinAttributeSet : public URuinAttributeSetBase
{
	GENERATED_BODY()
public:

	URuinAttributeSet();

	// Attribute Set Overrides.
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Used to create a local copy of Damage which is then subtracted from Current Health.
	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, Damage)

		// Used to create a local copy of Healing which is then added to Current Health.
	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, Healing)

		// Holds the current value for Health.
	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, CurrentHealth)

		// Holds the value for Maximum Health.
	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData MaximumHealth;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, MaximumHealth)

		// Holds the value for Health Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, HealthRegeneration)
};
