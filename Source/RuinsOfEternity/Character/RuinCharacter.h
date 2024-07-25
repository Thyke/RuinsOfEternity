// // Copyright (C) 2023 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RuinCharacter.generated.h"

class URuinAbilitySystemComponent;
class URuinHealthComponent;
class URuinCharacterMovementComponent;

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
protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
};
