// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class unrealsi1EditorTarget : TargetRules
{
	public unrealsi1EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings	= BuildSettingsVersion.Latest;
		IncludeOrderVersion		= EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] 
		{
            "unrealsi1",
            "urs_core",
            "urs_render",
        });
    }
}
