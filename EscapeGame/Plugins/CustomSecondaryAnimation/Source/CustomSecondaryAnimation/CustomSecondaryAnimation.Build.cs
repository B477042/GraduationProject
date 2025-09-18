// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomSecondaryAnimation : ModuleRules
{
	public CustomSecondaryAnimation(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AnimGraphRuntime",
				"AnimationCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
	}
}
