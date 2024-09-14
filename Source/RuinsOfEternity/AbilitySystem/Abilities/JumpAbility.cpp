﻿// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/Abilities/JumpAbility.h"
#include "RuinGameplayTags.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/RuinAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UJumpAbility::UJumpAbility(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    ActivationGroup = ERuinAbilityActivationGroup::Independent;
    ActivationPolicy = ERuinAbilityActivationPolicy::WhileInputActive;
    AbilityTags.AddTag(RuinGameplayTags::Ability_Type_Action_Jump);
    ActivationOwnedTags.AddTag(RuinGameplayTags::Event_Ability_Jump);
    ActivationBlockedTags.AddTag(RuinGameplayTags::Movement_Mode_Falling);
    ActivationBlockedTags.AddTag(RuinGameplayTags::Movement_Mode_Flying);

    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        FAbilityTriggerData TriggerData;
        TriggerData.TriggerTag = RuinGameplayTags::GameplayEvent_OnJumped;
        TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
        AbilityTriggers.Add(TriggerData);
    }
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
        if (Character)
        {
            Character->Jump();

            // Trigger gameplay event
            UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("GameplayEvent.OnLanded")), nullptr, true);
            if (WaitGameplayEventTask)
            {
                WaitGameplayEventTask->EventReceived.AddDynamic(this, &UJumpAbility::OnLanded);
                WaitGameplayEventTask->OnlyTriggerOnce = true;
                WaitGameplayEventTask->ReadyForActivation();
            }
        }
        else
        {
            CancelAbility(Handle, ActorInfo, ActivationInfo, true);
        }
    }
    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }
}
void UJumpAbility::OnLanded(FGameplayEventData Payload)
{
    // End ability
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // End ability logging
    FString AbilityName = GetName();
    FString EndType = bWasCancelled ? "Cancelled" : "Ended";
    UE_LOG(LogTemp, Warning, TEXT("Ability %s: %s"), *AbilityName, *EndType);
}