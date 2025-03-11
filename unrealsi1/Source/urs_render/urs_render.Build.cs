// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class urs_render : ModuleRules
{
	public urs_render(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //PrivatePCHHeaderFile = "ThirdPerson_PCH.h";

        PublicDependencyModuleNames.AddRange(new string[] 
		{
        // --- urs
            "urs_core"
        // --- 
            , "ProceduralMeshComponent"
            ,
        // --- unreals
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

            Path.Combine(rootDir, "urs_render"),
            Path.Combine(rootDir, "urs_render/src"),
        });
    }
}
