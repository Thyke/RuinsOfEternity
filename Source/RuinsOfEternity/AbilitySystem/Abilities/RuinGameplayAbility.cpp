// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "AbilitySystem/Abilities/RuinGameplayAbility.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RuinGameplayAbility)

URuinGameplayAbility::URuinGameplayAbility(const FObjectInitializer& ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnly;
}
