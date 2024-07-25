// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Animation/Nodes/RuinAnimNode_GameplayTagsBlend.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstanceProxy.h"
FRuinAnimNode_GameplayTagsBlend::FRuinAnimNode_GameplayTagsBlend()
    : AbilitySystemComponent(nullptr)
{
}

void FRuinAnimNode_GameplayTagsBlend::InitializeAbilitySystem(UAbilitySystemComponent* InASC)
{
    AbilitySystemComponent = InASC;
}

void FRuinAnimNode_GameplayTagsBlend::Update_AnyThread(const FAnimationUpdateContext& Context)
{
    AnimInstanceProxy = Context.AnimInstanceProxy;
    FAnimNode_BlendListBase::Update_AnyThread(Context);
}

int32 FRuinAnimNode_GameplayTagsBlend::GetActiveChildIndex()
{
    if (AnimInstanceProxy)
    {
        USkeletalMeshComponent* SkeletalMeshComponent = AnimInstanceProxy->GetSkelMeshComponent();
        if (SkeletalMeshComponent)
        {
            if (AActor* OwningActor = SkeletalMeshComponent->GetOwner())
            {
                if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
                {
                    TArray<FGameplayTag> ActiveGameplayTags;
                    ASC->GetOwnedGameplayTags().GetGameplayTagArray(ActiveGameplayTags);

                    for (const auto& Tag : ActiveGameplayTags)
                    {
                        int32 Index = Tags.Find(Tag);
                        if (Index != INDEX_NONE)
                        {
                            return Index + 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

const TArray<FGameplayTag>& FRuinAnimNode_GameplayTagsBlend::GetTags() const
{
    return GET_ANIM_NODE_DATA(TArray<FGameplayTag>, Tags);
}


#if WITH_EDITOR
void FRuinAnimNode_GameplayTagsBlend::RefreshPosePins()
{
    const auto Difference = BlendPose.Num() - GetTags().Num() - 1;
    if (Difference == 0)
    {
        return;
    }

    if (Difference > 0)
    {
        for (auto i = Difference; i > 0; i--)
        {
            RemovePose(BlendPose.Num() - 1);
        }
    }
    else
    {
        for (auto i = Difference; i < 0; i++)
        {
            AddPose();
        }
    }
}
#endif