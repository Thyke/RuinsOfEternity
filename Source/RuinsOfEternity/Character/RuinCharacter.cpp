// // Copyright (C) 2023 Thyke. All Rights Reserved.


#include "Character/RuinCharacter.h"
#include "Components/RuinCharacterMovementComponent.h"
#include "Components/RuinHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"

ARuinCharacter::ARuinCharacter(const FObjectInitializer& ObjectInitializer) : Super{
	ObjectInitializer.SetDefaultSubobjectClass<URuinCharacterMovementComponent>(CharacterMovementComponentName)
}
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<URuinAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(false);

	HealthComponent = CreateDefaultSubobject<URuinHealthComponent>(TEXT("HealthComponent"));

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

void ARuinCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

