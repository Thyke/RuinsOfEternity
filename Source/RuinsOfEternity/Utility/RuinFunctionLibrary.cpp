// // Copyright (C) 2024 Thyke. All Rights Reserved.


#include "Utility/RuinFunctionLibrary.h"
#include "GameplayTagsManager.h"

FName URuinFunctionLibrary::GetSimpleTagName(const FGameplayTag& Tag)
{
	const auto TagNode{ UGameplayTagsManager::Get().FindTagNode(Tag) };

	return TagNode.IsValid() ? TagNode->GetSimpleTagName() : NAME_None;
}
