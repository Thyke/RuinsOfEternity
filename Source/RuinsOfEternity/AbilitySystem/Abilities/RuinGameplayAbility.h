// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RuinGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ERuinAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

UENUM(BlueprintType)
enum class ERuinAbilityActivationGroup : uint8
{
	// Ability runs independently of all other abilities.
	Independent,

	// Ability is canceled and replaced by other exclusive abilities.
	Exclusive_Replaceable,

	// Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking,

	MAX	UMETA(Hidden)
};

UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by Ruins Of Eternity Game."))
class RUINSOFETERNITY_API URuinGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class URuinAbilitySystemComponent;
public:
	URuinGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	ERuinAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	ERuinAbilityActivationGroup GetActivationGroup() const { return ActivationGroup; }

protected:
	virtual void OnPawnAvatarSet();

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnPawnAvatarSet")
	void K2_OnPawnAvatarSet();


	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ruin|Ability Activation")
	ERuinAbilityActivationPolicy ActivationPolicy;

	// Defines the relationship between this ability activating and other abilities activating.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ruin|Ability Activation")
	ERuinAbilityActivationGroup ActivationGroup;
};
