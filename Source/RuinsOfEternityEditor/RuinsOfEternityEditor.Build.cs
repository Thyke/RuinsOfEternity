using UnrealBuildTool;

public class RuinsOfEternityEditor : ModuleRules
{
    public RuinsOfEternityEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                // Ekstra public include pathleriniz varsa buraya ekleyin
				"RuinsOfEternityEditor"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                // Ekstra private include pathleriniz varsa buraya ekleyin
            }
        );
        bEnableNonInlinedGenCppWarnings = true;
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine", "AnimationModifiers", "AnimationBlueprintLibrary", "RuinsOfEternity"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",

            }
        );

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new[]
            {
                "AnimGraph", "AnimGraphRuntime", "BlueprintGraph"
            });
        }
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {

            }
        );
    }
}
