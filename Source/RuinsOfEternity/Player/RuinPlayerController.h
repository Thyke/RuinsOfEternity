// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RuinPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RUINSOFETERNITY_API ARuinPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
