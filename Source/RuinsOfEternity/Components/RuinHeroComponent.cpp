// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Components/RuinHeroComponent.h"
#include "Input/RuinEnhancedInputComponent.h"
#include "Utility/RuinFunctionLibrary.h"
#include "Character/Hero/RuinHeroCharacter.h"
#include "RuinGameplayTags.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "AbilitySystem/RuinAbilitySystemGlobals.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(RuinHeroComponent)

URuinHeroComponent::URuinHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void URuinHeroComponent::BeginPlay()
{
	Super::BeginPlay();
}


void URuinHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	if (!InputConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("InputConfig Asset is not valid"));
		return;
	}

	URuinEnhancedInputComponent* RuinInputComponent = Cast<URuinEnhancedInputComponent>(PlayerInputComponent);
	if (!RuinInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent is not of type URuinEnhancedInputComponent"));
		return;
	}

	TArray<uint32> BindHandles;

	RuinInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed,
		&ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
}

void URuinHeroComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	ARuinHeroCharacter* Owner = Cast<ARuinHeroCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not of type ARuinHeroCharacter"));
		return;
	}
	URuinAbilitySystemComponent* RuinASC = URuinFunctionLibrary::GetRuinAbilitySystemComponent(Owner);
	if (RuinASC)
	{
		RuinASC->AbilityInputTagPressed(InputTag);
	}
}

void URuinHeroComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	ARuinHeroCharacter* Owner = Cast<ARuinHeroCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not of type ARuinHeroCharacter"));
		return;
	}

	if (URuinAbilitySystemComponent* RuinASC = URuinFunctionLibrary::GetRuinAbilitySystemComponent(Owner))
	{
		RuinASC->AbilityInputTagReleased(InputTag);
	}
}