// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "RuinFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RUINSOFETERNITY_API URuinFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Ruin|Utility", Meta = (AutoCreateRefTerm = "Tag", ReturnDisplayName = "Tag Name"))
	static FName GetSimpleTagName(const FGameplayTag& Tag);

	UFUNCTION(BlueprintPure, Category = "Ruin|Components", Meta = (BlueprintThreadSafe))
	static URuinAbilitySystemComponent* GetRuinAbilitySystemComponent(const AActor* Actor);

};
