#pragma once

#include "AnimGraphNode_BlendListBase.h"
#include "Animation/Nodes/RuinAnimNode_GameplayTagsBlend.h"
#include "RuinAnimGraphNode_GameplayTagsBlend.generated.h"

UCLASS()
class RUINSOFETERNITYEDITOR_API URuinAnimGraphNode_GameplayTagsBlend : public UAnimGraphNode_BlendListBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FRuinAnimNode_GameplayTagsBlend Node;

public:
	URuinAnimGraphNode_GameplayTagsBlend();

    virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;

    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

    virtual FText GetTooltipText() const override;

    virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& PreviousPins) override;

    virtual FString GetNodeCategory() const override;

    virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 PinIndex) const override;

protected:
    static void GetBlendPinProperties(const UEdGraphPin* Pin, bool& bBlendPosePin, bool& bBlendTimePin);
};
