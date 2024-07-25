#include "Nodes/RuinAnimGraphNode_GameplayTagsBlend.h"
#include "Utility/RuinFunctionLibrary.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(RuinAnimGraphNode_GameplayTagsBlend)

#define LOCTEXT_NAMESPACE "RuinGameplayTagsBlendAnimationGraphNode"

URuinAnimGraphNode_GameplayTagsBlend::URuinAnimGraphNode_GameplayTagsBlend()
{
	Node.AddPose();
}

void URuinAnimGraphNode_GameplayTagsBlend::PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent)
{
	if (ChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(FRuinAnimNode_GameplayTagsBlend, Tags))
	{
		Node.RefreshPosePins();
		ReconstructNode();
	}

	Super::PostEditChangeProperty(ChangedEvent);
}

FText URuinAnimGraphNode_GameplayTagsBlend::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Title", "Blend Poses by Gameplay Tag");
}

FText URuinAnimGraphNode_GameplayTagsBlend::GetTooltipText() const
{
	return LOCTEXT("Tooltip", "Blend Poses by Gameplay Tag");
}

void URuinAnimGraphNode_GameplayTagsBlend::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& PreviousPins)
{
	Node.RefreshPosePins();
	Super::ReallocatePinsDuringReconstruction(PreviousPins);
}

FString URuinAnimGraphNode_GameplayTagsBlend::GetNodeCategory() const
{
	return FString{TEXTVIEW("Ruin")};
}

void URuinAnimGraphNode_GameplayTagsBlend::CustomizePinData(UEdGraphPin* Pin, const FName SourcePropertyName, const int32 PinIndex) const
{
	Super::CustomizePinData(Pin, SourcePropertyName, PinIndex);

	bool bBlendPosePin;
	bool bBlendTimePin;
	GetBlendPinProperties(Pin, bBlendPosePin, bBlendTimePin);

	if (!bBlendPosePin && !bBlendTimePin)
	{
		return;
	}

	FString PinName = PinIndex <= 0
		? FString("Default")
		: PinIndex > Node.Tags.Num()
		? FString("Invalid")
		: URuinFunctionLibrary::GetSimpleTagName(Node.Tags[PinIndex - 1]).ToString();

	if (bBlendPosePin)
	{
		Pin->PinFriendlyName = FText::Format(LOCTEXT("PosePin", "{0} Pose"), FText::FromString(PinName));
	}
	else if (bBlendTimePin)
	{
		Pin->PinFriendlyName = FText::Format(LOCTEXT("BlendTimePin", "{0} Blend Time"), FText::FromString(PinName));
	}
}

void URuinAnimGraphNode_GameplayTagsBlend::GetBlendPinProperties(const UEdGraphPin* Pin, bool& bBlendPosePin, bool& bBlendTimePin)
{
	const auto PinFullName = Pin->PinName.ToString();
	const auto SeparatorIndex = PinFullName.Find(TEXT("_"), ESearchCase::CaseSensitive);

	if (SeparatorIndex <= 0)
	{
		bBlendPosePin = false;
		bBlendTimePin = false;
		return;
	}

	const auto PinName = PinFullName.Left(SeparatorIndex);
	bBlendPosePin = PinName == TEXT("BlendPose");
	bBlendTimePin = PinName == TEXT("BlendTime");
}

#undef LOCTEXT_NAMESPACE
