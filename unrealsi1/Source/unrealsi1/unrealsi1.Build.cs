// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class unrealsi1 : ModuleRules
{
	public unrealsi1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
		// --- urs ---
            "urs_core",
            "urs_render",
		// --- unreal ---
            "UMG",			   
			"Slate",		   
			"SlateCore",	   
            "ApplicationCore",
            "RenderCore",
            "RHI",
            "Projects",
		// --- Default ---
			"Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "HeadMountedDisplay",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        string rootDir = "";
        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(rootDir, "unrealsi1"),
            Path.Combine(rootDir, "unrealsi1/tutorial/src"),
            Path.Combine(rootDir, "unrealsi1/game/app/src"),

            Path.Combine(rootDir, "urs_core/src"),
        });
    }
}
