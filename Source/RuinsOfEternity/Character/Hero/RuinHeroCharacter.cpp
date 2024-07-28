// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Character/Hero/RuinHeroCharacter.h"
#include "RuinGameplayTags.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/RuinHeroComponent.h"

ARuinHeroCharacter::ARuinHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HeroComponent = CreateDefaultSubobject<URuinHeroComponent>(TEXT("HeroComponent"));
}

void ARuinHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (HeroComponent)
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}

void ARuinHeroCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ARuinHeroCharacter::NextTickLandedEvent, Hit));
}

void ARuinHeroCharacter::NextTickLandedEvent(FHitResult Hit)
{
	FGameplayTag LandedTag = RuinGameplayTags::GameplayEvent_OnLanded;
	FGameplayEventData EventData;
	EventData.EventTag = LandedTag;
	EventData.Instigator = this;
	EventData.Target = this;
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();//UAbilitySystemBlueprintLibrary::MakeEffectContext(this);
	EffectContext.AddHitResult(Hit);
	EventData.ContextHandle = EffectContext;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, LandedTag, EventData);
}

