using UnrealBuildTool;

public class CustomSecondaryAnimationEditor : ModuleRules
{
    public CustomSecondaryAnimationEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "AssetTools",
                "Slate",
                "SlateCore",
                "PropertyEditor",
                "CustomSecondaryAnimation",
                "BlueprintGraph",
                "AnimGraph",
                "AnimGraphRuntime",
                "AnimationCore"
            }
        );
    }
}