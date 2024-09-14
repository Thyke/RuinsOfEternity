// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RuinCharacter.generated.h"

class URuinAbilitySystemComponent;
class URuinHealthComponent;
class URuinCharacterMovementComponent;
class URuinAttributeSet;

UCLASS()
class RUINSOFETERNITY_API ARuinCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARuinCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintReadOnly, Category = "Ruin|Character")
	TObjectPtr<URuinCharacterMovementComponent> RuinCharacterMovement;

	UFUNCTION(BlueprintCallable, Category = "Ruin|Character")
	URuinAbilitySystemComponent* GetRuinAbilitySystemComponent() const;

	//AbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ruin|Components")
	TObjectPtr<URuinAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ruin|Components")
	TObjectPtr<URuinHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ruin|Attributes")
	TObjectPtr<URuinAttributeSet> AttributeSet;
protected:
	virtual void BeginPlay() override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	void SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void PostInitializeComponents() override;
};
