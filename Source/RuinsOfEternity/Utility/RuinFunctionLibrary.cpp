// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Utility/RuinFunctionLibrary.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/RuinHealthComponent.h"

FName URuinFunctionLibrary::GetSimpleTagName(const FGameplayTag& Tag)
{
	const auto TagNode{ UGameplayTagsManager::Get().FindTagNode(Tag) };

	return TagNode.IsValid() ? TagNode->GetSimpleTagName() : NAME_None;
}

URuinAbilitySystemComponent* URuinFunctionLibrary::GetRuinAbilitySystemComponent(const AActor* Actor)
{
    if (!IsValid(Actor))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Actor passed to GetRuinAbilitySystemComponent."));
        return nullptr;
    }

    UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
    if (!ASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("URuinAbilitySystemUtility: Owner ASC is not of URuinAbilitySystemComponent type"));
        return nullptr;
    }

    URuinAbilitySystemComponent* RuinASC = Cast<URuinAbilitySystemComponent>(ASC);
    if (!RuinASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("ASC `%s` from `%s` Owner is not of URuinAbilitySystemComponent type."), *GetNameSafe(ASC), *GetNameSafe(Actor));
        return nullptr;
    }

    return RuinASC;
}
