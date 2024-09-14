// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/RuinCharacter.h"
#include "RuinHeroCharacter.generated.h"

UCLASS()
class RUINSOFETERNITY_API ARuinHeroCharacter : public ARuinCharacter
{
	GENERATED_BODY()

public:

	ARuinHeroCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ruin|Components")
	TObjectPtr<class URuinHeroComponent> HeroComponent;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
