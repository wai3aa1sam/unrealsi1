// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class urs_core : ModuleRules
{
	public urs_core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage            = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions   = true;

        PublicDependencyModuleNames.AddRange(new string[] 
		{
            "UMG",			   
			"Slate",		   
			"SlateCore",	   
            "ApplicationCore",
            "RenderCore",
            "Renderer",
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
            Path.Combine(rootDir, "external"),

            Path.Combine(rootDir, "urs_core"),
            Path.Combine(rootDir, "urs_core/src"),
        });
    }
}
