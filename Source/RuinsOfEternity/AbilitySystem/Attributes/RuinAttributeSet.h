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

	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Ruin Attribute Set")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(URuinAttributeSet, MaxStamina)
};
