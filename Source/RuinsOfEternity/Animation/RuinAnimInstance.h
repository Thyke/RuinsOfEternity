// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h"
#include "RuinAnimInstance.generated.h"

class UAbilitySystemComponent;

UCLASS()
class RUINSOFETERNITY_API URuinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	URuinAnimInstance(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeAbilitySystem(UAbilitySystemComponent* ASC);
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
protected:

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
