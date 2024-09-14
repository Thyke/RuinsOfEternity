// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "Abilities/RuinGameplayAbility.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(RuinAbilitySystemComponent)

URuinAbilitySystemComponent::URuinAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void URuinAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	FGameplayAbilityActorInfo* ActorInfo = AbilityActorInfo.Get();
	check(ActorInfo);
	check(InOwnerActor);

	const bool bHasNewPawnAvatar = Cast<APawn>(InAvatarActor) && (InAvatarActor != ActorInfo->AvatarActor);
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	if (bHasNewPawnAvatar)
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			URuinGameplayAbility* RuinAbilityCDO = Cast<URuinGameplayAbility>(AbilitySpec.Ability);
			if (!RuinAbilityCDO)
			{
				continue;
			}

			if (RuinAbilityCDO->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
			{
				TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
				for (UGameplayAbility* AbilityInstance : Instances)
				{
					URuinGameplayAbility* RuinAbilityInstance = Cast<URuinGameplayAbility>(AbilityInstance);
					if (RuinAbilityInstance)
					{
						RuinAbilityInstance->OnPawnAvatarSet();
					}
				}
			}
			else
			{
				RuinAbilityCDO->OnPawnAvatarSet();
			}
		}

		GrantDefaultAbilitiesAndAttributes(InOwnerActor, InAvatarActor, this);
	}
}


void URuinAbilitySystemComponent::GrantDefaultAbilitiesAndAttributes(AActor* InOwnerActor, AActor* InAvatarActor, UObject* SourceObject)
{
	UE_LOG(LogTemp, Verbose, TEXT("Owner: %s, Avatar: %s"), *GetNameSafe(InOwnerActor), *GetNameSafe(InAvatarActor));

	if (!InOwnerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("InOwnerActor is null."));
		return;
	}

	for (int32 Index = 0; Index < GrantedAbilities.Num(); ++Index)
	{
		const FRuinAbilityInputMapping& AbilityToGrant = GrantedAbilities[Index];
		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid ability to grant at index: [%d]."), Index);
			continue;
		}

		URuinGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<URuinGameplayAbility>();
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel, INDEX_NONE, SourceObject);
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
		if (!AbilitySpecHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to grant ability: %s"), *AbilityToGrant.Ability->GetName());
		}
	}

	for (const FRuinAttributeSetDefinition& AttributeSetDefinition : GrantedAttributes)
	{
		if (!AttributeSetDefinition.AttributeSet)
		{
			continue;
		}

		const bool bHasAttributeSet = GetAttributeSubobject(AttributeSetDefinition.AttributeSet) != nullptr;
		UE_LOG(LogTemp, Verbose, TEXT("HasAttributeSet: %s (%s)"), bHasAttributeSet ? TEXT("true") : TEXT("false"), *GetNameSafe(AttributeSetDefinition.AttributeSet));

		if (!bHasAttributeSet)
		{
			UAttributeSet* AttributeSet = NewObject<UAttributeSet>(InOwnerActor, AttributeSetDefinition.AttributeSet);
			if (AttributeSetDefinition.InitializationData)
			{
				AttributeSet->InitFromMetaDataTable(AttributeSetDefinition.InitializationData);
			}
			AddAttributeSetSubobject(AttributeSet);
		}
	}
}

void URuinAbilitySystemComponent::GrantStartupEffects()
{
	for (const FActiveGameplayEffectHandle AddedEffect : AddedEffects)
	{
		RemoveActiveGameplayEffect(AddedEffect);
	}

	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	AddedEffects.Empty(GrantedEffects.Num());

	for (const TSubclassOf<UGameplayEffect> GameplayEffect : GrantedEffects)
	{
		FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), this);
			AddedEffects.Add(EffectHandle);
		}
	}
}

void URuinAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	//UE_LOG(LogTemp, Log, TEXT("AbilityInputTagPressed called with InputTag: %s"), *InputTag.ToString());

	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				//UE_LOG(LogTemp, Log, TEXT("AbilityInputTagPressed: Adding AbilitySpec.Handle: %s"), *AbilitySpec.Handle.ToString());
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void URuinAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	//UE_LOG(LogTemp, Log, TEXT("AbilityInputTagReleased called with InputTag: %s"), *InputTag.ToString());

	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				//UE_LOG(LogTemp, Log, TEXT("AbilityInputTagReleased: Adding AbilitySpec.Handle: %s"), *AbilitySpec.Handle.ToString());
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void URuinAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput called with DeltaTime: %f, bGamePaused: %d"), DeltaTime, bGamePaused);

	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const URuinGameplayAbility* RuinAbilityCDO = Cast<URuinGameplayAbility>(AbilitySpec->Ability);
				if (RuinAbilityCDO && RuinAbilityCDO->GetActivationPolicy() == ERuinAbilityActivationPolicy::WhileInputActive)
				{
					//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: Adding AbilitySpec.Handle: %s to AbilitiesToActivate"), *AbilitySpec->Handle.ToString());
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;
				//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: AbilitySpec.InputPressed set to true for AbilitySpec.Handle: %s"), *AbilitySpec->Handle.ToString());

				if (AbilitySpec->IsActive())
				{
					//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: AbilitySpec.Handle: %s is active, calling AbilitySpecInputPressed"), *AbilitySpec->Handle.ToString());
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const URuinGameplayAbility* RuinAbilityCDO = Cast<URuinGameplayAbility>(AbilitySpec->Ability);

					if (RuinAbilityCDO && RuinAbilityCDO->GetActivationPolicy() == ERuinAbilityActivationPolicy::OnInputTriggered)
					{
						//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: Adding AbilitySpec.Handle: %s to AbilitiesToActivate (OnInputTriggered)"), *AbilitySpec->Handle.ToString());
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: Trying to activate ability with AbilitySpecHandle: %s"), *AbilitySpecHandle.ToString());
		TryActivateAbility(AbilitySpecHandle);
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;
				//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: AbilitySpec.InputPressed set to false for AbilitySpec.Handle: %s"), *AbilitySpec->Handle.ToString());

				if (AbilitySpec->IsActive())
				{
					//UE_LOG(LogTemp, Log, TEXT("ProcessAbilityInput: AbilitySpec.Handle: %s is active, calling AbilitySpecInputReleased"), *AbilitySpec->Handle.ToString());
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}


void URuinAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void URuinAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	GrantStartupEffects();
}

bool URuinAbilitySystemComponent::IsAbilityActive(const FGameplayTagContainer* WithTags, const FGameplayTagContainer* WithoutTags, UGameplayAbility* Ignore)
{
	ABILITYLIST_SCOPE_LOCK();

	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (!Spec.IsActive() || Spec.Ability == nullptr || Spec.Ability == Ignore)
		{
			continue;
		}

		const bool WithTagPass = (!WithTags || Spec.Ability->AbilityTags.HasAny(*WithTags));
		const bool WithoutTagPass = (!WithoutTags || !Spec.Ability->AbilityTags.HasAny(*WithoutTags));

		if (WithTagPass && WithoutTagPass)
		{
			return true;
		}
	}
	return false;
}

bool URuinAbilitySystemComponent::IsAbilityActive(const FGameplayAbilitySpecHandle& InHandle)
{
	ABILITYLIST_SCOPE_LOCK();
	FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(InHandle);
	return Spec ? Spec->IsActive() : false;
}

bool URuinAbilitySystemComponent::IsAbilityActive(TSubclassOf<URuinGameplayAbility> AbilityClass, UObject* SourceObject)
{
	ABILITYLIST_SCOPE_LOCK();

	FGameplayAbilitySpec* Spec;

	if (SourceObject)
	{
		Spec = FindAbilitySpecByClassAndSource(AbilityClass, SourceObject);
	}
	else
	{
		Spec = FindAbilitySpecFromClass(AbilityClass);
	}

	if (Spec)
	{
		return Spec->IsActive();
	}
	return false;
}

FGameplayAbilitySpec* URuinAbilitySystemComponent::FindAbilitySpecFromTag(FGameplayTag Tag)
{
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.Ability->AbilityTags.HasTagExact(Tag))
		{
			return &Spec;
		}
	}

	return nullptr;
}

FGameplayAbilitySpec* URuinAbilitySystemComponent::FindAbilitySpecByClassAndSource(TSubclassOf<UGameplayAbility> AbilityClass, UObject* SourceObject)
{
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.Ability->GetClass() == AbilityClass && Spec.SourceObject == SourceObject)
		{
			return &Spec;
		}
	}
	return nullptr;
}