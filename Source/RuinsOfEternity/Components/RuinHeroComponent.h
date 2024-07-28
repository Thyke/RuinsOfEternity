// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RuinHeroComponent.generated.h"

class URuinInputConfig;
struct FGameplayTag;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUINSOFETERNITY_API URuinHeroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	URuinHeroComponent(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ruin|Input")
	URuinInputConfig* InputConfig;

public:	
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
};
