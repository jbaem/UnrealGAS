// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealGAS : ModuleRules
{
	public UnrealGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "Niagara"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { 

        });

		PublicIncludePaths.AddRange(new string[] {
			"UnrealGAS",
			"UnrealGAS/Variant_Platforming",
			"UnrealGAS/Variant_Platforming/Animation",
			"UnrealGAS/Variant_Combat",
			"UnrealGAS/Variant_Combat/AI",
			"UnrealGAS/Variant_Combat/Animation",
			"UnrealGAS/Variant_Combat/Gameplay",
			"UnrealGAS/Variant_Combat/Interfaces",
			"UnrealGAS/Variant_Combat/UI",
			"UnrealGAS/Variant_SideScrolling",
			"UnrealGAS/Variant_SideScrolling/AI",
			"UnrealGAS/Variant_SideScrolling/Gameplay",
			"UnrealGAS/Variant_SideScrolling/Interfaces",
			"UnrealGAS/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
