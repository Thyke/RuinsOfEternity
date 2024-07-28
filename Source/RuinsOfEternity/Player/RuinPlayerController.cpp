// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Player/RuinPlayerController.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "Utility/RuinFunctionLibrary.h"
#include "AbilitySystemGlobals.h"
void ARuinPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	//UE_LOG(LogTemp, Log, TEXT("PreProcessInput called with DeltaTime: %f, bGamePaused: %d"), DeltaTime, bGamePaused);
	Super::PreProcessInput(DeltaTime, bGamePaused);
}

void ARuinPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	//UE_LOG(LogTemp, Log, TEXT("PostProcessInput called with DeltaTime: %f, bGamePaused: %d"), DeltaTime, bGamePaused);

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PostProcessInput: No controlled pawn found"));
		return;
	}

	if (URuinAbilitySystemComponent* RuinASC = URuinFunctionLibrary::GetRuinAbilitySystemComponent(ControlledPawn))
	{
		//UE_LOG(LogTemp, Log, TEXT("PostProcessInput: Found RuinAbilitySystemComponent, processing ability input"));
		RuinASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("PostProcessInput: No RuinAbilitySystemComponent found for controlled pawn"));
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
