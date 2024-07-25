// // Copyright (C) 2023 Thyke. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimNodes/AnimNode_BlendListBase.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "RuinAnimNode_GameplayTagsBlend.generated.h"

/**
 * 
 */
USTRUCT()
struct RUINSOFETERNITY_API FRuinAnimNode_GameplayTagsBlend : public FAnimNode_BlendListBase
{
    GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, Category = "Settings", Meta = (FoldProperty))
    TArray<FGameplayTag> Tags;
#endif

public:
    FRuinAnimNode_GameplayTagsBlend();
    virtual ~FRuinAnimNode_GameplayTagsBlend() override = default;

    void InitializeAbilitySystem(UAbilitySystemComponent* InASC);
    virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

protected:
    virtual int32 GetActiveChildIndex() override;
    FAnimInstanceProxy* AnimInstanceProxy;
private:
    UAbilitySystemComponent* AbilitySystemComponent;

public:
    const TArray<FGameplayTag>& GetTags() const;

#if WITH_EDITOR
    void RefreshPosePins();
#endif
};