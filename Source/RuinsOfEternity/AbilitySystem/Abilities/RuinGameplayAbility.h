// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RuinGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by Ruins Of Eternity Game."))
class RUINSOFETERNITY_API URuinGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class URuinAbilitySystemComponent;
public:
	URuinGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
