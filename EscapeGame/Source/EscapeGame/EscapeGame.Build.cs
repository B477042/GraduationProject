// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class EscapeGame : ModuleRules
{
	public EscapeGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG","AIModule","NavigationSystem", "GameplayTasks", "Json", "JsonUtilities", "SlateCore","EngineSettings", "MoviePlayer", "AnimatedTexture", "Paper2D" });

		PrivateDependencyModuleNames.AddRange(new string[] {"GameSetting"  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        bLegacyPublicIncludePaths = false;


        //Faster Build https://answers.unrealengine.com/questions/3647/how-to-improve-compile-times-for-a-c-project.html
        //MinFilesUsingPrecompiledHeaderOverride = 1;
        //bFasterWithoutUnity = true;

    }
}
