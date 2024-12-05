// Copyright Epic Games, Inc. All Rights Reserved.

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

        PrivateIncludePaths.Add("unrealsi1");
        PrivateIncludePaths.Add("unrealsi1/src");

        PrivateIncludePaths.Add("unrealsi1/external");

        PrivateIncludePaths.Add("unrealsi1/tutorial/src");
        PrivateIncludePaths.Add("unrealsi1/core/src");
    }
}
