// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RuinsOfEternity : ModuleRules
{
	public RuinsOfEternity(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[]
        {
            "RuinsOfEternity"
        });

        PrivateIncludePaths.AddRange(new string[]
        {

        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "AIModule",
            "Niagara",
            "AnimGraphRuntime", "RigVM", "ControlRig",
            });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "InputCore",
            "EngineSettings",
            "PhysicsCore",
            "Slate",
            "SlateCore",
            "UMG",
            "GameplayMessageRuntime",
            "AnimationLocomotionLibraryRuntime",
            });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
