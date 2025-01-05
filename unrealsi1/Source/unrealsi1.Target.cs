// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class unrealsi1Target : TargetRules
{
	public unrealsi1Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings	= BuildSettingsVersion.Latest;
		IncludeOrderVersion		= EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("unrealsi1");
	}
}
