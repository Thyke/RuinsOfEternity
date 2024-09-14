// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Character/RuinCharacter.h"
#include "Components/RuinCharacterMovementComponent.h"
#include "Components/RuinHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/RuinAttributeSet.h"
#include "RuinGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Abilities/JumpAbility.h"
ARuinCharacter::ARuinCharacter(const FObjectInitializer& ObjectInitializer) : Super{
	ObjectInitializer.SetDefaultSubobjectClass<URuinCharacterMovementComponent>(CharacterMovementComponentName)
}
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<URuinAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(false);

	HealthComponent = CreateDefaultSubobject<URuinHealthComponent>(TEXT("HealthComponent"));

	AttributeSet = CreateDefaultSubobject<URuinAttributeSet>(TEXT("AttributeSet"));

	GetCapsuleComponent()->InitCapsuleSize(30.0f, 90.0f);

	if (IsValid(GetMesh()))
	{
		GetMesh()->SetRelativeLocation_Direct({ 0.0f, 0.0f, -92.0f });
		GetMesh()->SetRelativeRotation_Direct({ 0.0f, -90.0f, 0.0f });

		GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickMontagesWhenNotRendered;
		GetMesh()->bEnableUpdateRateOptimizations = false;
	}

	RuinCharacterMovement = Cast<URuinCharacterMovementComponent>(GetCharacterMovement());

#if WITH_EDITOR
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("Mesh") })->SetPropertyFlags(CPF_DisableEditOnInstance);
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("CapsuleComponent") })->SetPropertyFlags(CPF_DisableEditOnInstance);
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("CharacterMovement") })->SetPropertyFlags(CPF_DisableEditOnInstance);
#endif
}

URuinAbilitySystemComponent* ARuinCharacter::GetRuinAbilitySystemComponent() const
{
	return Cast<URuinAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ARuinCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARuinCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARuinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARuinCharacter::Landed(const FHitResult& Hit)
{
	if (URuinAbilitySystemComponent* RuinASC = Cast<URuinAbilitySystemComponent>(AbilitySystemComponent))
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this, RuinASC, Hit]()
			{
				if (RuinASC->IsAbilityActive(UJumpAbility::StaticClass(), nullptr))
				{
					FGameplayTag LandedTag = RuinGameplayTags::GameplayEvent_OnLanded;
					FGameplayEventData EventData;
					EventData.EventTag = LandedTag;
					EventData.Instigator = this;
					EventData.Target = this;
					FGameplayEffectContextHandle EffectContext = RuinASC->MakeEffectContext();
					EffectContext.AddHitResult(Hit);
					EventData.ContextHandle = EffectContext;
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, LandedTag, EventData);
					UE_LOG(LogTemp, Log, TEXT("Gameplay Event Sent - Tag: %s, Instigator: %s, Target: %s"),
						*LandedTag.ToString(),
						*GetNameSafe(EventData.Instigator),
						*GetNameSafe(EventData.Target));
				}
			});
	}
	Super::Landed(Hit);
}

void ARuinCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ARuinCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	URuinCharacterMovementComponent* RuinMoveComp = CastChecked<URuinCharacterMovementComponent>(GetCharacterMovement());

	SetMovementModeTag(PrevMovementMode, PreviousCustomMode, false);
	SetMovementModeTag(RuinMoveComp->MovementMode, RuinMoveComp->CustomMovementMode, true);
}

void ARuinCharacter::SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled)
{
	if (URuinAbilitySystemComponent* RuinASC = GetRuinAbilitySystemComponent())
	{
		const FGameplayTag* MovementModeTag = nullptr;
		if (MovementMode == MOVE_Custom)
		{
			MovementModeTag = RuinGameplayTags::CustomMovementModeTagMap.Find(CustomMovementMode);
		}
		else
		{
			MovementModeTag = RuinGameplayTags::MovementModeTagMap.Find(MovementMode);
		}

		if (MovementModeTag && MovementModeTag->IsValid())
		{
			RuinASC->SetLooseGameplayTagCount(*MovementModeTag, (bTagEnabled ? 1 : 0));
		}
	}
}