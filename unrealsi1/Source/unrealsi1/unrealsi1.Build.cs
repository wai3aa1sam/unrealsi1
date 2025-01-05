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
        
        PublicIncludePaths.Add(Path.Combine(rootDir, "unrealsi1/external"));

        PublicIncludePaths.Add(Path.Combine(rootDir, "unrealsi1"));
        PublicIncludePaths.Add(Path.Combine(rootDir, "unrealsi1/core/src"));
        PublicIncludePaths.Add(Path.Combine(rootDir, "unrealsi1/tutorial/src"));
        PublicIncludePaths.Add(Path.Combine(rootDir, "unrealsi1/game/app/src"));
    }
}
