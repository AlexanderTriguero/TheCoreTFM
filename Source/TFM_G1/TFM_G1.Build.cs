// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TFM_G1 : ModuleRules
{
	public TFM_G1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
