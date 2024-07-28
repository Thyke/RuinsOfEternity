// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "RuinAbilitySystemComponent.generated.h"


class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;
class URuinGameplayAbility;

USTRUCT(BlueprintType)
struct FRuinAbilityInputMapping
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URuinGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FRuinAttributeSetDefinition
{
	GENERATED_BODY()

	/** Attribute Set to grant */
	UPROPERTY(EditAnywhere, Category = Attributes)
	TSubclassOf<UAttributeSet> AttributeSet;

	/** Data table reference to initialize the attributes with, if any (can be left unset) */
	UPROPERTY(EditAnywhere, Category = Attributes, meta = (RequiredAssetDataTags = "RowStructure=/Script/GameplayAbilities.AttributeMetaData"))
	TObjectPtr<UDataTable> InitializationData = nullptr;
};

UCLASS()
class RUINSOFETERNITY_API URuinAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	URuinAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;



	//Startup
	virtual void GrantDefaultAbilitiesAndAttributes(AActor* InOwnerActor, AActor* InAvatarActor, UObject* SourceObject);
	void GrantStartupEffects();

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

	UPROPERTY(EditDefaultsOnly, Category = "Ruin|Abilities")
	TArray<FRuinAbilityInputMapping> GrantedAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ruin|Effects")
	TArray<TSubclassOf<UGameplayEffect>> GrantedEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Ruin|Attributes")
	TArray<FRuinAttributeSetDefinition> GrantedAttributes;

protected:
	virtual void BeginPlay() override;

	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that have their input held.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	UPROPERTY(transient)
	TArray<FActiveGameplayEffectHandle> AddedEffects;
};
