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