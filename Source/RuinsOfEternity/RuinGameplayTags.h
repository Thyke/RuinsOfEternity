// // Copyright (C) 2024 Thyke. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace RuinGameplayTags
{


	//Jump Ability Tags
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Type_Action_Jump);
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Ability_Jump);

	//Gameplay Events
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_OnLanded);

	// Based On Lyra Starter Game
	RUINSOFETERNITY_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	RUINSOFETERNITY_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	RUINSOFETERNITY_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	RUINSOFETERNITY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
}